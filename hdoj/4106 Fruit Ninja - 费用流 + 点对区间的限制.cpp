#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 2500
#define maxm 1000000
const int inf = 1 << 30;
int eh[maxn], p[maxn], low[maxn], tot, dist[maxn];
int s, t, n, m, k;
int ans, anscost;
int val[maxn];
bool visit[maxn];
int que[1000000], head, tail;
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
	head = tail = 0;
	memset(visit, false, sizeof(visit));
	memset(p, -1, sizeof(p));
	memset(low, 0, sizeof(low));
	for(int i = 0; i < maxn; i++) dist[i] = -inf;
	visit[s] = true, low[s] = inf, dist[s] = 0;
	que[tail++] = s;
	while(head < tail) {
		int u = que[head++];
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
			if(cap - flow && dist[u] + cost > dist[v]) {
				dist[v] = dist[u] + cost;
				p[v] = i;
				low[v] = min(low[u], cap - flow);
				if(!visit[v]) {
					que[tail++] = v;
					visit[v] = true;
				}
			}
		}
	}
	return dist[t] != -inf;
}

void costflow() {
	ans = anscost = 0;
	while(spfa()) {
		int x = p[t];
		ans += low[t];
		anscost += low[t] * dist[t];
		while(x != -1) {
			et[x].flow += low[t];
			et[x^1].flow -= low[t];
			x = p[et[x].u];
		}
	}
}

int main() {
	while(~scanf("%d%d%d", &n, &m, &k)) {
		init();
		m = min(n, m);
		int sum = 0;
		s = 0, t = 2 * n + 1;
        addedge(s, 1, 0, k);
        addedge(2 * n, t, 0, k);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &val[i]);
			sum += val[i];
			addedge(i, i + n, val[i], 1);
			if(i + 1 <= n) {
                addedge(i, i + 1, 0, inf);
                addedge(i + n, i + n + 1, 0, inf);
            }
			if(i + m <= n) addedge(i + n, i + m, 0, inf);
		}
		if(m == k) {
			printf("%d\n", sum);
			continue;
		}
		costflow();
		printf("%d\n", anscost);
	}
	return 0;
}
