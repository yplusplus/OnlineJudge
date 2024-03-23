#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 20005
#define maxm 1000005
const int INF = 99999999;
int s, t, n, m;
int low[maxn], dist[maxn], pre[maxn], cur[maxn], tot, eh[maxn], cnt[maxn];

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
	int u, v, now;
	memset(dist, 0, sizeof(dist));
	memset(low, 0, sizeof(low));
	 for(u = 0; u <= n; u++) cur[u] = eh[u];
	low[s] = 0, cnt[0] = n;
	u = s;
	int flow = 0;
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
				flow += low[t];
				low[s] = INF;
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
	int u, v, cap, i;
	scanf("%d%d", &n, &m);
	init();
	s = 0, t = n + 1;
	for(i = 1; i <= n; i++) {
		scanf("%d", &cap);
		addedge(s, i, cap);
		scanf("%d", &cap);
		addedge(i, t, cap);
	}
	for(i = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &cap);
		addedge(u, v, cap);
		addedge(v, u, cap);
	}
	printf("%d\n", isap(s, t, t - s + 1));
	return 0;
}