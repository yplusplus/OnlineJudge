#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
const int inf = 1 << 30;
#define maxn 50500
#define maxm 500000
int n, m, l, r;
int eh[maxn], tot, dist[maxn];
bool visit[maxn];
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

void spfa(int s) {
	queue<int> que;
	fill(&dist[0], &dist[maxn], -inf);
	memset(visit, false, sizeof(visit));
	dist[s] = 0, visit[s] = true;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i !=- 1; i = et[i].next) {
			int v = et[i].v, w = et[i].w;
			if(dist[v] < dist[u] + w) {
				dist[v] = dist[u] + w;
				if(!visit[v]) {
					que.push(v);
					visit[v] = true;
				}
			}
		}
	}
}

int main() {
	int a, b, c;
	while(~scanf("%d", &n)) {
		init();
		r = 0;
	//	l = inf;
		for(int i = 0; i < n; i++) {
			scanf("%d%d%d", &a, &b, &c);
			r = max(r, ++b);
	//		l = min(l, a);
			addedge(a, b, c);
		}
		for(int i = 1; i <= r; i++) {
			addedge(i - 1, i, 0);
			addedge(i, i - 1, -1);
		}
		spfa(0);
		printf("%d\n", dist[r]);
	}
	return 0;
}