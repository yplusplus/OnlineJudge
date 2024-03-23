#include "iostream"
#include "cstring"
using namespace std;
#define maxn 50005
#define maxm 2000005
#define bigint __int64
const bigint INF = 1 << 29;

typedef struct edge {
	int u, v;
	bigint cap, flow;
	int next;
}edge;

int eh[maxn], tot;
edge et[maxm];
int gap[maxn], pre[maxn], cur[maxn], dist[maxn], a[maxn];
int s, t;

void add(int u, int v, bigint cap, bigint flow) {
	edge E = {u, v, cap, flow, eh[u]};
	et[tot] = E;
	eh[u] = tot++;
}

void addedge(int u, int v, bigint cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

bigint min(bigint a, bigint b) {
	return a < b ? a : b;
}

bigint sap_gap(int s, int t, int n) {
	int u, v, now;
	memset(dist, 0, sizeof(dist));
	memset(a, 0, sizeof(a));
	for(u = 0; u <= n; u++)
		cur[u] = eh[u];
	bigint maxflow = 0;
	u = s;
	a[s] = INF, gap[s] = n;
	while(dist[s] < n) {
		for(now = cur[u]; now != -1; now = et[now].next)
			if(et[now].cap - et[now].flow && dist[u] == dist[v = et[now].v] + 1)
				break;
		if(now != -1) {
			cur[u] = pre[v] = now;
			a[v] = min(a[u], et[now].cap - et[now].flow);
			u = v;
			if(u == t) {
				for(; u != s; u = et[pre[u]].u) {
					et[pre[u]].flow += a[t];
					et[pre[u] ^ 1].flow -= a[t];
				}
				maxflow += a[t];
				a[s] = INF;
			}
		}
		else {
			if(--gap[dist[u]] == 0)
				break;
			dist[u] = n;
			cur[u] = eh[u];
			for(now = cur[u]; now != -1; now = et[now].next)
				if(et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1)
					dist[u] = dist[et[now].v] + 1;
			gap[dist[u]]++;
			if(u != s)
				u = et[pre[u]].u;
		}
	}
	return maxflow;
}

int main() {
	int n, f, d;
	int u, v, i, j;
	int fn, dn;

	while(cin >> n >> f >> d) {
		init();
		s = 0;
		t = f + d + 2 * n + 1;

		for(i = 1; i <= f; i++)
			addedge(s, i, 1);

		for(i = 1; i <= d; i++)
			addedge(f + 2 * n + i, t, 1);

		for(i = 1; i <= n; i++)
			addedge(f + i, f + n + i, 1);

		for(i = 1; i <= n; i++) {
			cin >> fn >> dn;
			for(j = 0; j < fn; j++) {
				cin >> u;
				addedge(u, f + i, 1);
			}
			for(j = 0; j < dn; j++) {
				cin >> v;
				addedge(f + n + i, f + 2 * n + v, 1);
			}
		}
		printf("%I64d\n", sap_gap(s, t, t - s + 1));
	}
	return 0;
}


