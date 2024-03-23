#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define maxm 1000005
#define maxn 50005
#define MAX 55
const int INF = 99999999;
int eh[maxn], tot, low[maxn], p[maxn], dist[maxn];
int s, t;
int ans, anscost;
int fans, fanscost;
bool visit[maxn];
int cap[MAX][MAX], need[MAX][MAX], cost[MAX][MAX][MAX];
struct Edge {
	int u, v, cost, cap, flow, next;
}et[maxm];

void add(int u, int v, int cost, int cap, int flow) {
	Edge E = {u, v, cost, cap, flow, eh[u]};
	et[tot] = E;
	eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap) {
	add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

int min(int a, int b) {
	return a < b ? a : b;
}

bool spfa() {
	queue<int> que;
	memset(visit, false, sizeof(visit));
	memset(p, -1, sizeof(p));
	fill(&dist[0], &dist[maxn], INF);
	visit[s] = true, low[s] = INF, dist[s] = 0;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, cost = et[i].cost, flow = et[i].flow, cap = et[i].cap;
			if(cap - flow && dist[u] + cost < dist[v]) {
				dist[v] = dist[u] + cost;
				p[v] = i;
				low[v] = min(low[u], cap - flow);
				if(!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
	}
	return dist[t] != INF;
}

void costflow() {
	ans = 0, anscost = 0;
	while(spfa()) {
		int x = p[t];
		ans += low[t];
		anscost += low[t] * dist[t];
		while(x != -1) {
			et[x].flow += low[t];
			et[x^1].flow -= low[t];
			et[x^1].cost = -et[x].cost;
			x = p[et[x].u];
		}
	}
}

int main() {
	int n, m, k;
	int i, j, l;
	while(1) {
		int sum = 0;
		fans = fanscost = 0;
		scanf("%d%d%d", &n, &m, &k);
		if(!n && !m && !k) break;
		for(i = 1; i <= n; i++) {
			for(j = 1; j <= k; j++) {
				scanf("%d", &need[i][j]);
				sum += need[i][j];
			}
		}
		for(i = 1; i <= m; i++) {
			for(j = 1; j <= k; j++) {
				scanf("%d", &cap[i][j]);
			}
		}
		for(i = 1; i <= k; i++) {
			for(j = 1; j <= n; j++) {
				for(l = 1; l <= m; l++) {
					scanf("%d", &cost[i][j][l]);
				}
			}
		}
		for(i = 1; i <= k; i++) {
			init();
			s = 0; t = n + m + 1;
			for(j = 1; j <= m; j++) {
				addedge(s, j, 0, cap[j][i]);
				for(l = 1; l <= n; l++)
					addedge(j, m + l, cost[i][l][j], INF);
			}
			for(j = 1; j <= n; j++)
				addedge(m + j, t, 0, need[j][i]);
			costflow();
			fans += ans, fanscost += anscost;
		}
		if(sum != fans) fanscost = -1;
		printf("%d\n", fanscost);		
	}
	return 0;
}