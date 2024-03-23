#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 5005
#define maxm 500005
#define MAX 55
const int INF = 1 << 30;
int eh[maxn], pre[maxn], cur[maxn], dist[maxn], cnt[maxn], low[maxn], tot;
int n, m, s, t, r, c, sum;
int color[MAX][MAX];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

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
	memset(low, 0, sizeof(low));
	memset(dist, 0, sizeof(dist));
	memset(cnt, 0, sizeof(cnt));
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

int pos1(int i, int j) {
	return (i - 1) * c + j;
}

int pos2(int i, int j) {
	return r * c + (i - 1) * c + j;
}

int main() {
	int tn, gval, sval, tt = 1, gold[MAX][MAX], silver[MAX][MAX];
	scanf("%d", &tn);
	init();
	while(tt <= tn) {
		isap_init();
		scanf("%d%d%d%d", &r, &c, &gval, &sval);
		for(int i = 1; i <= r; i++)
			for(int j = 1; j <= c; j++)
				scanf("%d", &gold[i][j]);
		for(int i = 1; i <= r; i++)
			for(int j = 1; j <= c; j++)
				scanf("%d", &silver[i][j]);
		s = 0, t = r * c * 2 + 1;
		for(int i = 1; i <= r; i++) {
			for(int j = 1; j <= c; j++) {
				sum += gold[i][j] + silver[i][j];
				if(color[i][j]) {
					addedge(s, pos1(i, j), gold[i][j]);
					addedge(pos1(i, j), pos2(i, j), INF);
					addedge(pos2(i, j), t, silver[i][j]);
					for(int k = 0; k < 4; k++) {
						int x = i + dx[k], y = j + dy[k];
						if(x >= 1 && x <= r && y >= 1 && y <= c) {
							addedge(pos1(i, j), pos1(x, y), gval);
							addedge(pos2(x, y), pos2(i, j), sval);
						}
					}
				}
				else {
					addedge(s, pos2(i, j), silver[i][j]);
					addedge(pos2(i, j), pos1(i, j), INF);
					addedge(pos1(i, j), t, gold[i][j]);		
				}
			}
		}
		printf("Case %d: %d\n", tt++, sum - isap(s, t, t - s + 1));
	}
	return 0;
}