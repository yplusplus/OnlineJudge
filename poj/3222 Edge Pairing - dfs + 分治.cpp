#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 20005
#define maxm 200005
int n, m;
int eh[maxn], dfn[maxn], Dindex, tot;
struct Edge {
	int v, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v) {
	Edge e = {v, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

int dfs(int u) {
	int pre = -1;				//u��ǰ��
	dfn[u] = ++Dindex;			//ʱ���
	for(int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if(!dfn[v]) {
			int cur = dfs(v);	//v�ĺ��
			if(cur != -1) printf("%d %d %d\n", u, v, cur);
			else if(pre == -1) pre = v;
			else {
				printf("%d %d %d\n", pre, u, v);
				pre = -1;
			}
		} else if(dfn[u] < dfn[v]) {
			if(pre == -1) pre = v;
			else {
				printf("%d %d %d\n", pre, u, v);
				pre = -1;
			}
		}
	}
	return pre;
}

void solve() {
	Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
//	for(int i = 1; i <= n; i++)		//��Ϊ��Ŀ˵����ͨͼ������ֻ��Ҫ������һ����dfs������������ͼ
//		if(!dfn[i])
			dfs(1);
}
int main() {
	while(~scanf("%d%d", &n, &m)) {
		init();
		for(int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			addedge(u, v), addedge(v, u);
		}
		solve();
	}
	return 0;
}