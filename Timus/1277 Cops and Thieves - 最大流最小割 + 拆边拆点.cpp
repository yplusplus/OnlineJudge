#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 205
#define maxm 100005
const int INF = 999999999;
int n, m, s, t, k;
int cap[maxn];
int eh[maxn], cur[maxn], pre[maxn], dist[maxn], cnt[maxn], low[maxn], tot;

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
	Edge E = {u, v, cap, flow, eh[u]};
	et[tot] = E;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

int isap(int s, int t, int n) {
	int u, v, now, flow = 0;
	memset(dist, 0, sizeof(dist));
	memset(cnt, 0, sizeof(cnt));
	memset(low, 0, sizeof(low));
	for(u = 0; u <= n; u++) cur[u] = eh[u];
	low[s] = INF, cnt[0] = n;
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
				low[s] = INF, flow += low[t];
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

int main() {
	int u, v;
	scanf("%d%d%d%d%d", &k, &n, &m, &s, &t);
	init();
	for(int i = 1; i <= n; i++) scanf("%d", &cap[i]);
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		addedge(u + n, v, INF);
		addedge(v + n, u, INF);
	}
	cap[s] = cap[t] = INF;
	for(int i = 1; i <= n; i++) addedge(i, n + i, cap[i]);
	if(s != t && isap(s, t, 2 * n) <= k) printf("YES\n");
	else printf("NO\n");
	return 0;
}