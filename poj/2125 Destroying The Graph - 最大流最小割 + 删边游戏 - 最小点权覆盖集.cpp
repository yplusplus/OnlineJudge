#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
const int inf = 1 << 30;
#define maxn 250
#define maxm 15000
int n, m, s, t, k;
int out[maxn], in[maxn];
int eh[maxn], pre[maxn], cur[maxn], dist[maxn], tot, cnt[maxn], low[maxn];
int col[maxn];
struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

void init() {
	tot = k = 0;
	memset(eh, -1, sizeof(eh));
	memset(col, 0, sizeof(col));
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
	memset(dist, 0, sizeof(dist));
	memset(low, 0, sizeof(low));
	memset(cnt, 0, sizeof(cnt));
	for(u = 0; u <= n; u++) cur[u] = eh[u];
	low[s] = inf, cnt[0] = n;
	u = s;
	while(dist[s] < n) {
		for(now = cur[u]; now != -1; now = et[now].next)
			if(et[now].cap - et[now].flow && dist[u] == dist[v = et[now].v] + 1)
				break;
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

void dfs(int u) {
	col[u] = 1;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if(et[i].cap - et[i].flow && !col[v])
			dfs(v);
	}
}

int main() {
	while(~scanf("%d%d", &n, &m)) {
		init();
		s = 0, t = n * 2 + 1;
		for(int i = 1; i <= n; i++) scanf("%d", &in[i]), addedge(n + i, t, in[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &out[i]), addedge(s, i, out[i]);
		for(int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			addedge(u, n + v, inf);
		}
		printf("%d\n", isap(s, t, t - s + 1));
		dfs(s);
		for(int i = 1; i <= n; i++) {
			if(col[i] == 0) k++;
			if(col[i + n] == 1) k++;
		}
		printf("%d\n", k);
		for(int i = 1; i <= n; i++) {
			if(col[i] == 0) printf("%d -\n", i);
			if(col[i + n] == 1) printf("%d +\n", i);
		}
	}
	return 0;
}