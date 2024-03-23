#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 1050
#define maxm 5000
int n, m;
int eh[maxn], tot, belong[maxn], bcc, dfn[maxn], low[maxn], Dindex;
int s[maxn], top, deg[maxn];
int bridge[maxm], bcnt;
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
void dfs(int u, int fa) {
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if(v == fa) continue;
		if(!dfn[v]) {
			dfs(v, u);
			low[u] = min(low[v], low[u]);
			if(low[v] > dfn[u]) {
	//			bridge[bcnt++] = i;	//记录桥
				bcc++;
				while(1) {
					belong[s[top]] = bcc;
					if(s[top--] == v) break;
				}
			}
		} else low[u] = min(low[u], dfn[v]);
	}
}
void tarjan() {
	bcnt = top = bcc = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	for(int i = 1; i <= n; i++) 
		if(!dfn[i])
			dfs(i, -1);
}
int main() {
	int u, v;
	while(~scanf("%d%d", &n, &m)) {
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			addedge(u, v), addedge(v, u);
		}
		tarjan();
		memset(deg, 0, sizeof(deg));
		for(int u = 1; u <= n; u++) {
			for(int i = eh[u]; i != -1; i = et[i].next) {
				int v = et[i].v;
				if(belong[u] != belong[v]) deg[belong[u]]++, deg[belong[v]]++;
			}
		}
		int cnt = 0;
		for(int i = 0; i <= bcc; i++) //bcc从0开始的
			if(deg[i] == 2) cnt++;
		printf("%d\n", (cnt + 1) / 2);
	}
	return 0;
}