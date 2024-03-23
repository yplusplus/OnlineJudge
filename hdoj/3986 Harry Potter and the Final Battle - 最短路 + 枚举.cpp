#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define maxn 1005
#define maxm 100500
const int inf = 1 << 30;
int n, m, s, x;
int eh[maxn], dist[maxn], pre[maxn], p[maxn], tot;
bool visit[maxn], flag;
struct Edge {
	int u, v, w, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int w) {
	Edge e = {u, v, w, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

int spfa() {
	queue<int> que;
	fill(dist, dist + maxn, inf);
	memset(visit, false, sizeof(visit));
	dist[s] = 0, visit[s] = true;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, w = et[i].w;
			if(dist[u] + w < dist[v] && i != x) {
				dist[v] = dist[u] + w;
				if(x == -1) pre[v] = i, p[v] = u;
				if(!visit[v]) {
					que.push(v);
					visit[v] = true;
				}
			}
		}
	}
	return dist[n];
}

int solve() {
	x = -1;
	int ans = spfa();
	if(ans == inf) return -1;
	for(int i = n; i != s; i = p[i]) {
		x = pre[i];
		ans = max(ans, spfa());
		if(ans == inf) return -1;
	}
	return ans;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		init();
		s = 1;
		for(int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w);
			addedge(v, u, w);
		}
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}