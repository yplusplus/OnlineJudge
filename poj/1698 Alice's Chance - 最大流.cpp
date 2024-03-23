#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 400
#define maxm 15000
const int inf = 1 << 30;
int n, m, s, t;
int eh[maxn], low[maxn], pre[maxn], cur[maxn], tot, cnt[maxn], dist[maxn];
int film[25][10], week, sum;
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

void build() {
	init();
	s = 0; t = n + week * 7 + 1;
	for(int i = 1; i <= n; i++) {
		addedge(s, i, film[i][8]);
		for(int j = 1; j <= film[i][9]; j++) {
			for(int k = 1; k <= 7; k++) {
				if(film[i][k]) addedge(i, n + (j - 1) * 7 + k, 1);
			}
		}
	}
	for(int i = 1; i <= week; i++)
		for(int j = 1; j <= 7; j++)
			addedge(n + (i - 1) * 7 + j, t, 1);
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		week = sum = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= 9; j++)
				scanf("%d", &film[i][j]);
			week = max(week, film[i][9]);
			sum += film[i][8];
		}
		build();
		int ans = isap(s, t, t - s + 1);
		if(ans == sum) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}