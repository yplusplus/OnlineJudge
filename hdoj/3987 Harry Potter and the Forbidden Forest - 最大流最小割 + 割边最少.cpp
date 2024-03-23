#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 1000
#define maxm 500000
const int inf = 1 << 30;
int s, t, n, m;
int eh[maxn], low[maxn], dist[maxn], cnt[maxn], tot, pre[maxn], cur[maxn];
bool color[maxn];
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
	memset(low, 0, sizeof(low));
	memset(cnt, 0, sizeof(cnt));
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
				if(et[now].cap - et[now].flow && dist[u] > dist[v = et[now].v] + 1)
					dist[u] = dist[v] + 1;
			cnt[dist[u]]++;
			if(u != s) u = et[pre[u]].u;
		}
	}
	return flow;
}

void dfs(int u) {
	color[u] = 1;
	for(int i = eh[u]; i != -1; i = et[i].next)
		if(!color[et[i].v] && et[i].cap - et[i].flow) 
			dfs(et[i].v);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int tt = 1; tt <= T; tt++) {
		scanf("%d%d", &n, &m);
		init();
		s = 0, t = n - 1;
		for(int i = 0; i < m; i++) {
			int u, v, cap, d;
			scanf("%d%d%d%d", &u, &v, &cap, &d);
			if(d) addedge(u, v, cap), addedge(v, u, cap);
			else addedge(u, v, cap);
		}
		isap(s, t, n);
		for(int i = 0; i < tot; i += 2) {
			if(et[i].cap == et[i].flow) et[i].cap = 1, et[i].flow = 0;
			else et[i].flow = 0;
			et[i^1].cap = et[i^1].flow = 0;
		}
		int ans = isap(s, t, n);
		printf("Case %d: %d\n", tt, ans);
	}
}