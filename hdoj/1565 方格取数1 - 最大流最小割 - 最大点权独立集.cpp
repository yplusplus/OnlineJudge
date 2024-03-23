#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 505
#define maxm 10005
#define MAX 25
const int INF = 1 << 30;
int nn, s, t, n, sum;
int eh[maxn], pre[maxn], cur[maxn], dist[maxn], low[maxn], cnt[maxn], tot;
int color[MAX][MAX], a[MAX][MAX];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

void init() {
	for(int i = 1; i < MAX; i++) {
		bool flag = i & 1;
		for(int j = 1; j < MAX; j++, flag = !flag)
			color[i][j] = flag;
	}
}

void isap_init() {
	tot = sum = 0;
	memset(eh, -1, sizeof(eh));
}

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

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
	memset(cnt, 0, sizeof(cnt));
	memset(dist, 0, sizeof(dist));
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
				for(; u != s; u =et[pre[u]].u) {
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

int pos(int i, int j) {
	return (i - 1) * nn + j;
}

int main() {
	init();
	while(scanf("%d", &nn) != EOF) {
		isap_init();
		s = 0; t = nn * nn + 1;
		for(int i = 1; i <= nn; i++) {
			for(int j = 1; j <= nn; j++) {
				scanf("%d", &a[i][j]);
				sum += a[i][j];
				if(color[i][j]) {
					addedge(s, pos(i, j), a[i][j]);
					for(int k = 0; k < 4; k++) {
						int x = i + dx[k], y = j + dy[k];
						if(x >= 1 && x <= nn && y >= 1 && y <= nn)
							addedge(pos(i, j), pos(x, y), INF);
					}
				}
				else addedge(pos(i, j), t, a[i][j]);
			}
		}
		printf("%d\n", sum - isap(s, t, t - s + 1));
	}
	return 0;
}