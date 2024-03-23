#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 810
#define maxm 50000
const int inf = 1 << 30;
int n, m, s, t;
int eh[maxn], low[maxn], dist[maxn], tot, pre[maxn], cur[maxn], cnt[maxn], color[maxn];

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

int isap(int s, int t, int n) {
	int u, v, now, flow = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(low, 0, sizeof(low));
	memset(dist, 0, sizeof(dist));
	for(u = 0; u <= n; u++) cur[u] = eh[u];
	low[s] = inf, cnt[0] = n;
	u = s;
	while(dist[s] < n) {
		for(now = cur[u]; now != -1; now = et[now].next)
			if(et[now].cap - et[now].flow && dist[u] == dist[v = et[now].v] + 1) break;
		if(now != -1) {
			cur[u] = pre[v] = now;
			low[v] = min(low[u], et[now].cap - et[now].flow);
			u = v;
			if(u == t) {
				for(; u != s; u = et[pre[u]].u) {
					et[pre[u]].flow += low[t];
					et[pre[u]^1].flow -= low[t];
				}
				low[s] = inf, flow += low[t];
			}
		} else {
			if(--cnt[dist[u]] == 0) break;
			dist[u] = n;
			cur[u] = eh[u];
			for(now = eh[u]; now != -1; now = et[now].next)
				if(et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1)
					dist[u] = dist[et[now].v] + 1;
			cnt[dist[u]]++;
			if(u != s) u = et[pre[u]].u;
		}
	}
	return flow;
}

void dfs1(int u) {
	color[u] = 1;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if(et[i].cap - et[i].flow && !color[v])
			dfs1(v);
	}
}

void dfs2(int u) {
	color[u] = 2;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if(et[i^1].cap - et[i^1].flow && !color[v])
			dfs2(v);
	}
}

int main() {
	int u, v, cap;
	while(scanf("%d%d%d%d", &n, &m, &s, &t) != EOF) {
		if(!n && !m && !s && !t) break;
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &u, &v, &cap);
			addedge(u, v, cap);
			addedge(v, u, cap);
		}
		isap(s, t, n);
		memset(color, 0, sizeof(color));
		dfs1(s), dfs2(t);
		int flag = 1;
		for(int i = 1; i <= n; i++)
			if(!color[i])
				flag = 0;
		if(flag) printf("UNIQUE\n");
		else printf("AMBIGUOUS\n");
	}
	return 0;
}