#include "iostream"
#include "algorithm"
using namespace std;
#define maxn 505
#define maxm 1000010
const int INF = 1 << 29;
typedef __int64 LL;

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

struct field {
	int cow, cap;
}field[maxn];

int eh[maxn], tot, tot1, dist[maxn], pre[maxn], cur[maxn], a[maxn], gap[maxn];
LL maz[maxn][maxn], time[maxn*maxn];
int s, t, n, m, cow;

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
	Edge E = {u, v, cap, flow, eh[u]};
	et[tot] = E;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

void floyd() {
	for(int k = 1 ; k <= n ; k ++ )
		for(int i = 1 ; i <= n ; i ++ )
			for(int j = 1 ; j <= n ; j ++ )
				if(maz[i][k] && maz[k][j]) {
					if(maz[i][j] == 0) maz[i][j] = maz[i][k] + maz[k][j];
					else maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
				}
	tot1 = 0;
	for(int i = 1 ; i <= n ; i ++ )
		for(int j = i + 1 ; j <= n ; j ++ )
			if(maz[i][j]) time[tot1++] = maz[i][j];	
	sort(time, time + tot1);
}

void build(LL limit) {
	int i, j;
	for(i = 1; i <= n; i++) {
		addedge(i, i + n, INF);
		if(field[i].cow) addedge(s, i, field[i].cow);
		if(field[i].cap) addedge(i + n, t, field[i].cap);
	}
	for(i = 1 ; i <= n ; i++)
		for(j = i + 1 ; j <= n ; j++)
			if(maz[i][j] && maz[i][j] <= limit)
				addedge(i, j + n, INF), addedge(j, i + n, INF);
}

int isap(int s, int t, int n) {
	int u, v, now;
	memset(dist, 0, sizeof(dist));
	memset(a, 0, sizeof(a));
	for(u = 0; u <= n; u++)	cur[u] = eh[u];
	int maxflow = 0;
	u = s, a[s] = INF, gap[0] = n;
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
					et[pre[u]^1].flow -= a[t];
				}
				maxflow += a[t], a[s] = INF;
			}
		} else {
			if(--gap[dist[u]] == 0)	break;
			dist[u] = n;
			cur[u] = eh[u];
			for(now = eh[u]; now != -1; now = et[now].next)
				if(et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1)
					dist[u] = dist[et[now].v] + 1;
			gap[dist[u]]++;
			if(u != s) u = et[pre[u]].u;
		}
	}
	return maxflow;
}


LL solve() {
	LL res = -1;
	int l = 0, r = tot1 - 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		init();
		build(time[mid]);
		if(isap(s, t, t - s + 1) == cow) res = time[mid], r = mid -1;
		else l = mid + 1;
	}
	return res;
}

int main() {
	int u, v, i;
	LL w;
	while(~scanf("%d%d", &n, &m)) {
		for(cow = 0, i = 1; i <= n; i++) {
			scanf("%d%d", &field[i].cow, &field[i].cap);
			cow += field[i].cow;
			fill(maz[i], maz[i] + n + 1, 0);
		}
		for(i = 1; i <= m; i++) {
			scanf("%d%d%I64d", &u, &v, &w);
			if(maz[u][v]) w = min(w, maz[u][v]);
			maz[u][v] = maz[v][u] = w;
		}
		s = 0, t = 2 * n + 1;
		floyd();
		printf("%I64d\n", solve());
	}
	return 0;
}