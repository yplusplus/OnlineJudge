#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
const int inf = 1 << 30;
#define maxn 5005
#define maxm 500000
int n, k, s, t;
int maz[55][55];
int eh[maxn], low[maxn], ans, anscost, tot, dist[maxn], pre[maxn];
bool visit[maxn];

struct Edge {
	int u, v, cost, cap, flow, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cost, int cap, int flow) {
	Edge e = {u, v, cost, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap) {
	add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}

bool spfa() {
	queue<int> que;
	fill(&dist[0], &dist[maxn], -inf);
	memset(visit, false, sizeof(visit));
	memset(low, 0, sizeof(low));
	memset(pre, -1, sizeof(pre));
	visit[s] = true, low[s] = inf, dist[s] = 0;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
			if(cap - flow && dist[u] + cost > dist[v]) {
				dist[v] = dist[u] + cost;
				pre[v] = i;
				low[v] = min(low[u], cap - flow);
				if(!visit[v]) {
					que.push(v);
					visit[v] = true;
				}
			}
		}
	}
	return dist[t] != -inf;
}

void costflow() {
	ans = anscost = 0;
	while(ans < k && spfa()) {
		int x = pre[t];
		ans += low[t];
		anscost += low[t] * dist[t];
		while(x != -1) {
			et[x].flow += low[t];
			et[x^1].flow -= low[t];
			x = pre[et[x].u];
		}
	}
}

int pos(int i, int j) {
	return (i - 1) * n + j;
}

void build() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			int u = pos(i, j);
			if(j + 1 <= n) addedge(n * n + u, pos(i, j + 1), 0, inf);
			if(i + 1 <= n) addedge(n * n + u, pos(i + 1, j), 0, inf);
		}
	}
	addedge(2 * n * n, t, 0, inf);
}

int main() {
	scanf("%d%d", &n, &k);
	init();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			scanf("%d", &maz[i][j]);
			int u = pos(i, j);
			addedge(u, n * n + u, maz[i][j], 1);
			addedge(u, n * n + u, 0, inf);
		}
	s = 1, t = 2 * n * n + 1;
	build();
	costflow();
	printf("%d\n", anscost);
	return 0;
}
