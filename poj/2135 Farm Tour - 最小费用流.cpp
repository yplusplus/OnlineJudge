#include "iostream"
#include "cstdio"
#include "string"
#include "queue"
using namespace std;
#define bigint __int64
#define maxn 1005
#define maxm 40005
const bigint INF = 99999999;
int n, m;
int s, t;
int eh[maxn], tot, p[maxn];
bigint dist[maxn], anscost;
bool visit[maxn];

struct Edge {
	int u, v;
	bigint cost, cap, flow;
	int next;
}et[maxm];

void add(int u, int v,bigint cost, bigint cap,bigint flow) {
	Edge e = {u, v, cost, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, bigint cost, bigint cap) {
	add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

bool spfa() {
	queue<int> que;
	memset(visit, false, sizeof(visit));
	memset(p, -1, sizeof(p));
	fill(&dist[0], &dist[maxn], INF);
	visit[s] = true, dist[s] = 0;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v;
			bigint cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
			if(flow < cap && dist[u] + cost < dist[v]) {
				dist[v] = dist[u] + cost;
				p[v] = i;
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
	anscost = 0;
	while(spfa()) {
		int x = p[t];
		anscost += dist[t];
		while(x != -1) {
			et[x].flow++;
			et[x^1].flow--;
	//		et[x^1].cost = -et[x].cost;
			x = p[et[x].u];
		}
	}
}

int main() {
	init();
	int u, v;
	bigint cost;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		scanf("%d%d%I64d", &u, &v, &cost);
		addedge(u, v, cost, 1);
		addedge(v, u, cost, 1);
	}
	s = 0, t = n;
	addedge(s, 1, 0, 2);
	costflow();
	printf("%I64d\n", anscost);
	return 0;
}