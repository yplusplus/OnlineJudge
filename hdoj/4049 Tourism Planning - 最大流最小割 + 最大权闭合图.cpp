#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
const int inf = 1 << 30;
#define maxn 2000 
#define maxm 20000
int n, m, s, t;
int eh[maxn], pre[maxn], low[maxn], cur[maxn], cnt[maxn], dist[maxn], tot;
int cost[15], ins[15][15], bonus[15][15], sum;
struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

void init() {
	tot = sum = 0;
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
	u = s, low[s] = inf, cnt[0] = n;
	while(dist[s] < n) {
		for(now = cur[u]; now != -1; now = et[now].next)
			if(et[now].cap - et[now].flow && dist[u] == dist[v = et[now].v] + 1) break;
		if(now != -1) {
			cur[u] = pre[v] = now;
			low[v] = min(low[u], et[now].cap - et[now].flow);
			u = v;
			if(u == t) {
				for(flow += low[t]; u != s; u = et[pre[u]].u) {
					et[pre[u]].flow += low[t];
					et[pre[u]^1].flow -= low[t];
				}
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

void build() {
	s = 0, t = n * m + n * n * m + 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(ins[i][j] > 0) {
				addedge(s, (i - 1) * m + j, ins[i][j]);
				sum += ins[i][j];
			} else addedge((i - 1) * m + j, t, -ins[i][j]);
			if(j > 1) addedge((i - 1) * m + j, (i - 1) * m + j - 1, inf);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			for(int k = 1; k <= m; k++) {
				addedge(s, n * m + ((i - 1) * n + j - 1) * m + k, bonus[i][j]);
				addedge(n * m + ((i - 1) * n + j - 1) * m + k, (i - 1) * m + k, inf);
				addedge(n * m + ((i - 1) * n + j - 1) * m + k, (j - 1) * m + k, inf);
				sum += bonus[i][j];
			}
		}
	}
}

int main() {
	while(~scanf("%d%d", &n, &m)) {
		if(!n && !m) break;
		init();
		for(int i = 1; i <= m; i++) scanf("%d", &cost[i]);
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				scanf("%d", &ins[i][j]);
				ins[i][j] -= cost[j];
			}
		}
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= n; j++)
				scanf("%d", &bonus[i][j]);
		build();
		int res = isap(s, t, t - s + 1);
		if(res == sum) printf("STAY HOME\n");
		else printf("%d\n", sum - res);
	}
	return 0;
}