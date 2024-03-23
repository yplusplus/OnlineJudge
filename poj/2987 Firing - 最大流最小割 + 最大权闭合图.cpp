#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
#define maxn 5005
#define maxm 100005
const int inf = 1 << 30;
int n, m, s, t;
int eh[maxn], dist[maxn], cur[maxn], pre[maxn], low[maxn], tot, cnt[maxn];
int w[maxn], num;
bool visit[maxn];

struct Edge {
	int u, v, cap ,flow, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e, eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u , v, cap, 0), add(v, u, 0, 0);
}

long long isap(int s, int t, int n) {
	int u, v, now;
	long long flow = 0;
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
				flow += low[t], low[s] = inf;
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
	visit[u] = true;
	for(int i = eh[u]; i != -1; i = et[i].next)
		if(et[i].cap - et[i].flow && !visit[et[i].v]) {
			num++;
			dfs(et[i].v);
		}
}

int main() {
	int u, v;
	init();
	scanf("%d%d", &n, &m);
	s = 0, t = n + 1;
	num = 0;
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
		if(w[i] > 0) addedge(s, i, w[i]), ans += w[i];
		else if(w[i] < 0) addedge(i, t, -w[i]);
	}
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		addedge(u, v, inf);
	}
	ans -= isap(s, t, t - s + 1);
	memset(visit, false, sizeof(visit));
	dfs(s);
	printf("%d %lld\n", num, ans);
}