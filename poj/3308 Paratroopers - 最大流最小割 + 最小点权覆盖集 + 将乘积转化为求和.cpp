#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;
#define maxn 105
#define maxm 100000
const int inf = 1 << 30;

int n, m, s, t, l;
int eh[maxn], cur[maxn], pre[maxn], dist[maxn], tot, cnt[maxn];
double low[maxn];

struct Edge {
	int u, v;
	double cap, flow;
	int next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, double cap, double flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, double cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

double isap(int s, int t, int n) {
	int u, v, now;
	double flow = 0;
	memset(dist, 0, sizeof(dist));
	memset(cnt, 0, sizeof(cnt));
	memset(low, 0, sizeof(low));
	for(u = 0; u <= n; u++) cur[u] = eh[u];
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
				flow += low[t], low[s] = inf;
			}
		} else {
			if(--cnt[dist[u]] == 0) break;
			dist[u] = n, cur[u] = eh[u];
			for(now = cur[u]; now != -1; now = et[now].next)
				if(et[now].cap - et[now].flow && dist[u] > dist[v = et[now].v] + 1)
					dist[u] = dist[v = et[now].v] + 1;
			cnt[dist[u]]++;
			if(u != s) u = et[pre[u]].u;
		}
	}
	return flow;
}

int main() {
	int T;
	double cost;
	scanf("%d", &T);
	while(T--) {
		init();
		scanf("%d%d%d", &m, &n, &l);
		s = 0, t = n + m + 1;
		for(int i = 1; i <= m; i++) {
			scanf("%lf", &cost);
			addedge(s, i, log(cost));
		}
		for(int i = 1; i <= n; i++) {
			scanf("%lf", &cost);
			addedge(i + m, t, log(cost));
		}
		for(int i = 1; i <= l; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			addedge(u, m + v, inf);
		}
		double ans = isap(s, t, t - s + 1);
		ans = exp(ans);
		printf("%.4f\n", ans);
	}
	return 0;
}