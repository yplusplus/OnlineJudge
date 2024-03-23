#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
#define maxn 105000 
#define maxm 1000000
int eh[maxn], tot, eh2[maxn], tot2;
int visit[maxn];
int dfn[maxn], low[maxn], Dindex, color[maxn];
int n, m, q;
struct Edge {
	int u, v, next;
}et[maxm], et2[maxm];

void init() {
	tot = tot2 = 0;
	memset(eh, -1, sizeof(eh));
	memset(eh2, -1, sizeof(eh2));
}

void addedge1(int u, int v) {
	Edge e = {u, v, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge2(int u, int v) {
	Edge e = {u, v, eh2[u]};
	et2[tot2] = e;
	eh2[u] = tot2++;
}

void dfs(int u, int pre) {
	dfn[u] = low[u] = ++Dindex;
	visit[u] = 1;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if(visit[v] == 1 && v != pre) low[u] = min(low[u], dfn[v]);
		if(visit[v] == 0) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) addedge2(u, v), addedge2(v, u);
		}
	}
	visit[u] = 2;
}

void tarjan() {
	Dindex = 0;
	memset(visit, 0, sizeof(visit));
	for(int i = 1; i <= n; i++) 
		if(!visit[i]) dfs(i, -1);
}

void colorful(int u, int idx) {
	color[u] = idx;
	for(int i = eh2[u]; i != -1; i = et2[i].next) {
		int v = et2[i].v;
		if(color[v]) continue;
		colorful(v, idx);
	}
}

int main() {
	int u, v;
	while(~scanf("%d%d%d", &n, &m, &q)) {
		if(!n && !m && !q) break;
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			addedge1(u, v), addedge1(v, u);
		}
		tarjan();
		memset(color, 0, sizeof(color));
		for(int i = 1, idx = 0; i <= n; i++) 
			if(!color[i]) idx++, colorful(i, idx);
		while(q--) {
			scanf("%d%d", &u, &v);
			if(color[u] == color[v]) printf("Y\n");
			else printf("N\n");
		}
		printf("-\n");
	}
	return 0;
}