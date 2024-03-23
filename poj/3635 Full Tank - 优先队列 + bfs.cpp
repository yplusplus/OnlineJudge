#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define maxn 1005
#define maxm 20050
const int inf = 1 << 30;
int n, m, q;
int eh[maxn], tot, val[maxn];
bool visit[maxn][105];

struct Edge {
	int u, v, dis, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int dis) {
	Edge e = {u, v, dis, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

struct node {
	int s, cost, oil;
	node() {}
	node(int a, int b, int c) {
		s = a, cost = b, oil = c;
	}
	bool operator< (const node &a) const {
		return cost > a.cost;
	}
};

int bfs(int cap, int s, int e) {
	memset(visit, false, sizeof(visit));
	priority_queue<node> que;
	que.push(node(s, 0, 0));
	while(!que.empty()) {
		node now = que.top();
		que.pop();
		if(now.s == e) return now.cost;
		if(visit[now.s][now.oil]) continue;
		visit[now.s][now.oil] = true;
		if(now.oil < cap && !visit[now.s][now.oil+1]) 
			que.push(node(now.s, now.cost + val[now.s], now.oil + 1));
		for(int i = eh[now.s]; i != -1; i = et[i].next)
			if(now.oil >= et[i].dis && !visit[et[i].v][now.oil-et[i].dis]) 
				que.push(node(et[i].v, now.cost, now.oil - et[i].dis));
	}
	return -1;
}

int main() {
	scanf("%d%d", &n, &m);
	init();
	for(int i = 0; i < n; i++) scanf("%d", &val[i]);
	for(int i = 0; i < m; i++) {
		int u, v, dis;
		scanf("%d%d%d", &u, &v, &dis);
		addedge(u, v, dis);
		addedge(v, u, dis);
	}
	scanf("%d", &q);
	for(int i = 0; i < q; i++) {
		int cap, s, e;
		scanf("%d%d%d", &cap, &s, &e);
		int ans = bfs(cap, s, e);
		if(ans == -1) printf("impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}
