#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 105
#define maxm 50000
const int inf = 1 << 30;
int n, m, s, t;
int eh[maxn], pre[maxn], cur[maxn], dist[maxn], low[maxn], cnt[maxn], tot;
int ans, max1, max2;
struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

void init() {
	tot = ans = 0;
	memset(eh, -1, sizeof(eh));
	ans = max1 = max2 = 0;
}

void add(int u, int v, int cap) {
	Edge e = {u, v, cap, 0, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap), add(v, u, 0);
}

int isap(int s, int t, int n) {
	int u, v, now, flow = 0;
	memset(dist, 0, sizeof(dist));
	memset(cnt, 0, sizeof(cnt));
	memset(low, 0, sizeof(low));
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
			dist[u] = n, cur[u] = eh[u];
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
	int T, tmp;
	scanf("%d", &T);
	while(T--) {
		init();
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; i++) {
			int u, v, cap;
			scanf("%d%d%d", &u, &v, &cap);
			addedge(u, v, cap);
		}
		s = 1, t = n;
		ans = isap(s, t, n);
		for(int i = eh[s]; i != -1; i = et[i].next) {
			if(tmp = et[i].cap - et[i].flow) {
				max1 = max(max1, tmp);
			}
		}
		for(int i = eh[t]; i != -1; i = et[i].next) {
			if(tmp = et[i^1].cap - et[i^1].flow) {
				max2 = max(max2, tmp);
			}
		}
		ans += min(max1, max2);
		printf("%d\n", ans);

	}
}