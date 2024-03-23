#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define maxn 105
#define maxm 10500
const int inf = 1 << 30;
int n, m, s, t;
int level[maxn], price[maxn];
int eh[maxn], tot, dist[maxn];
bool visit[maxn];
struct Edge {
	int u, v, cost, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int cost) {
	Edge e = {u, v, cost, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

int spfa(int low, int high) {
	queue<int> que;
	fill(&dist[0], &dist[maxn], inf);
	memset(visit, false, sizeof(visit));
	visit[s] = true, dist[s] = 0;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, cost = et[i].cost;
			if(level[v] >= low && level[v] <= high) {
				if(dist[u] + cost < dist[v]) {
					dist[v] = dist[u] + cost;
					if(v != t && !visit[v]) {
						que.push(v);
						visit[v] = true;
					}
				}
			}
		}
	}
	return dist[t];
}

int solve() {
	int ans = inf;
	for(int i = 0; i <= m; i++)//Ã¶¾ÙµÈ¼¶
		ans = min(ans, spfa(level[1] - m + i, level[1] + i));
	return ans;
}

int main() {
	int nn, v, cost;
	while(~scanf("%d%d", &m, &n)) {
		init();
		s = 1, t = n + 1;
		for(int u = 1; u <= n; u++) {
			scanf("%d%d%d", &price[u], &level[u], &nn);
			addedge(u, t, price[u]);
			for(int j = 0; j < nn; j++) {
				scanf("%d%d", &v, &cost);
				addedge(u, v, cost);
			}
		}
		level[t] = level[s];
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}