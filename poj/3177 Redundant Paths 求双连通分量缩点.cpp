#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 5050
#define maxm 25000
int n, m;
int eh[maxn], tot, dfn[maxn], low[maxn], Dindex;
int s[maxn], top, deg[maxn];
int bridge[maxm], bcnt;
int visit[maxn];
bool maz[maxn][maxn];
struct Edge {
	int u, v, next;
}et[maxm];
void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}
void addedge(int u, int v) {
	Edge e = {u, v, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}
void dfs(int u, int fa) {
	dfn[u] = low[u] = ++Dindex;
	visit[u] = 1;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if(visit[v] == 1 && v != fa) low[u] = min(low[u], dfn[v]);
		if(visit[v] == 0) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) bridge[bcnt++] = i;	//ге
		}
	}
	visit[u] = 2;
}
void tarjan() {
	top = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(visit, 0, sizeof(visit));
	for(int i = 1; i <= n; i++) 
		if(!dfn[i])
			dfs(i, -1);
}
int main() {
	int u, v;
	while(~scanf("%d%d", &n, &m)) {
		init();
		memset(maz, false, sizeof(maz));
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			if(!maz[u][v]) maz[u][v] = true, addedge(u, v), addedge(v, u);
		}
		tarjan();
		memset(deg, 0, sizeof(deg));
		for(int u = 1; u <= n; u++) {
			for(int i = eh[u]; i != -1; i = et[i].next) {
				int v = et[i].v;
				if(low[u] != low[v]) deg[low[u]]++, deg[low[v]]++;
			}
		}
		int cnt = 0;
		for(int i = 0; i <= n; i++) 
			if(deg[i] == 2) cnt++;
		printf("%d\n", (cnt + 1) / 2);
	}
	return 0;
}
