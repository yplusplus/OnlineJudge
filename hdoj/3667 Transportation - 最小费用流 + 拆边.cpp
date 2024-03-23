#include "iostream"
#include "cstring"
#include "cstdio"
#include "queue"
using namespace std;
#define maxn 105
#define maxm 100005
const int inf = 1 << 30;
int n, m, k, s, t;
int eh[maxn], low[maxn], tot, dist[maxn], pre[maxn], ans, anscost;
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
	fill(&dist[0], &dist[maxn], inf);
	memset(visit, false, sizeof(visit));
	memset(pre, -1, sizeof(pre));
	low[s] = inf, visit[s] = true, dist[s] = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
			if(cap - flow && dist[v] > dist[u] + cost) {
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
	return dist[t] != inf;
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

int main() {
	int u, v, cost, cap;
	while(~scanf("%d%d%d", &n, &m, &k)) {
		init();
		s = 1, t = n;
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d%d", &u, &v, &cost, &cap);
			for(int j = 1; j <= cap; j++)
				addedge(u, v, (2 * j - 1) * cost, 1);
		}
		costflow();
		if(ans == k) printf("%d\n", anscost);
		else printf("%d\n", -1);
	}
	return 0;
}