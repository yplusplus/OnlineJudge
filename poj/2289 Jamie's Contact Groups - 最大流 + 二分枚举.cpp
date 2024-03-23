#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
const int inf = 1 << 30;
#define maxn 1600
#define maxm 1000000
int n, m, s, t;
int eh[maxn], pre[maxn], cur[maxn], tot, low[maxn], cnt[maxn], dist[maxn];

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

struct person {
	int cnt, st[550];
	void init() {
		cnt = 0;
	}
}person[1100];

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
	memset(dist, 0, sizeof(dist));
	memset(low, 0, sizeof(low));
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
				flow += low[t], low[s] = inf;
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

bool build(int cap) {
	init();
	s = 0, t = n + m + 1;
	for(int i = 1; i <= n; i++) {
		addedge(s, i, 1);
		for(int j = 0; j < person[i].cnt; j++)
			addedge(i, person[i].st[j] + n + 1, 1);
	}
	for(int i = 1; i <= m; i++) addedge(i + n, t, cap);
	return isap(s, t, t - s + 1) == n;
}

int solve() {
	int l = 1, r = n, res = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(build(mid)) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

int main() {
	char ch, name[20];
	while(~scanf("%d%d", &n, &m)) {
		if(!n && !m) break;
		for(int i = 1; i <= n; i++) {
			scanf("%s", name);
			person[i].init();
			ch = getchar();
			while(ch != '\n') {
				scanf("%d", &person[i].st[person[i].cnt++]);
				ch = getchar();
			}
		}
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}