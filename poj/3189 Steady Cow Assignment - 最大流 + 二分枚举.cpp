#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 1100
#define maxm 150000
const int inf = 1 << 30;
int n, m, s, t, b;
int eh[maxn], low[maxn], pre[maxn], cur[maxn], tot, cnt[maxn], dist[maxn];
int cow[1005][25], cap[25];
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

bool build(int rank) {
	for(int st = 1; st <=  b - rank + 1; st++) {
		init();
		s = 0; t = n + b + 1;
		for(int i = 1; i <= n; i++) {
			addedge(s, i, 1);
			for(int j = st; j <= st + rank - 1; j++)
				addedge(i, n + cow[i][j], 1);
		}
		for(int i = 1; i <= b; i++) addedge(n + i, t, cap[i]);
		if(isap(s, t, t - s + 1) == n) return true;
	}
	return false;
}

int solve() {
	int l = 1, r = b, res = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(build(mid)) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &b);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= b; j++)
			scanf("%d", &cow[i][j]);
	for(int i = 1; i <= b; i++) scanf("%d", &cap[i]);
	int ans = solve();
	printf("%d\n", ans);
	return 0;
}
