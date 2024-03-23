#include "iostream"
#include "cstring"
#include "cstdio"
#include "cmath"
using namespace std;
#define maxn 1000
#define maxm 1000000
const double inf = 1 << 30;
int n, m, s;
double l, u;
bool visit[maxn];
int eh[maxn], tot;
double dist[maxn];
struct Edge {
	int u, v;
	double cost;
	int next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, double cost) {
	Edge e = {u, v, cost, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}
bool instack[maxn];
bool dfs_spfa(int u) {
	if(instack[u]) return false;
	instack[u] = true;
	visit[u] = true;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		double cost = et[i].cost;
		if(dist[v] > dist[u] + cost) {
			dist[v] = dist[u] + cost;
			if(!dfs_spfa(v)) return false;
		}
	}
	instack[u] = false;
	return true;
}

bool solve() {
	memset(visit, false, sizeof(visit));
	memset(instack, false, sizeof(instack));
	memset(dist, 0, sizeof(dist));
	for(int i = 1; i <= n + m; i++) {
		if(!visit[i])
			if(!dfs_spfa(i)) return false;
	}
	return true;
}

int main() {	double tmp;	while(scanf("%d%d%lf%lf", &n, &m, &l, &u) != EOF) {		init();		for(int i = 1; i <= n; i++) {			for(int j = 1; j <= m; j++) {				scanf("%lf", &tmp);				addedge(j + n, i, log(u / tmp));				addedge(i, j + n, -log(l / tmp));			}		}		if(solve()) printf("YES\n");		else printf("NO\n");	}		return 0;}