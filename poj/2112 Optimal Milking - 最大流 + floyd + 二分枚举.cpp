#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
using namespace std;
#define maxn 500
#define maxm 50005
const int INF = 999999999;
int k, c, m, n;

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];
int maz[maxn][maxn], ans[maxn * maxn];
int s, t, tot, tot1, eh[maxn], cur[maxn], pre[maxn], dist[maxn], low[maxn], cnt[maxn];

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

bool isap(int s, int t, int n) {
	int u, v, now;
	memset(dist, 0, sizeof(dist));
	memset(low, 0, sizeof(low));
	for(u = 0; u <= n; u++) cur[u] = eh[u];
	int flow = 0;
	u = s;
	low[s] = INF, cnt[0] = n;
	while(dist[s] < n) {
		for(now = cur[u]; now != -1; now = et[now].next)
			if(et[now].cap - et[now].flow && dist[u] == dist[v = et[now].v] + 1) break;
		if(now != -1) {
			cur[u] = pre[v] = now;
			low[v] = min(low[u], et[now].cap - et[now].flow);
			u = v;
			if(u == t) {
				for(; u != s; u = et[pre[u]].u) {
					et[pre[u]].flow += low[t];
					et[pre[u]^1].flow -= low[t];
				}
				flow += low[t], low[s] = INF;
			}
		} else {
			if(--cnt[dist[u]] == 0) break;
			dist[u] = n;
			cur[u] = eh[u];
			for(now = eh[u]; now != -1; now = et[now].next)
				if(et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1) 
					dist[u] = dist[et[now].v] + 1;
			cnt[dist[u]]++;
			if(u != s) u = et[pre[u]].u;
		}
	}
	return flow == c;
}

void floyd() {
	for(int l = 1; l <= n; l++) {
		for(int i = 1; i <= n; i++)
			if(maz[i][l])
			for(int j = 1; j <= n; j++) 
				if(maz[l][j] && i != j) {
					if(maz[i][j] == 0) maz[i][j] = maz[i][l] + maz[l][j];
					else maz[i][j] = min(maz[i][j], maz[i][l] + maz[l][j]);
				}
	}
	tot1 = 0;
	for(int i = 1; i <= n; i++) 
		for(int j = i + 1; j <= n; j++)
			ans[tot1++] = maz[i][j];
	sort(ans, ans + tot1);
}

void build(int limit) {
	init();
	for(int i = 1; i <= c; i++) 
		addedge(s, k + i, 1);
	for(int i = 1; i <= k; i++) {
		addedge(i, t, m);
		for(int j = 1; j <= c; j++) {
			if(maz[i][k + j] <= limit && maz[i][k + j])
				addedge(k + j, i, 1);
		}
	}
}
	
int solve() {
	int l = 0, r = tot1 - 1, res = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		build(ans[mid]);
		if(isap(s, t, t - s + 1)) res = ans[mid], r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

int main() {
	cin >> k >> c >> m;
	s = 0, t = k + c + 1;
	n = k + c;
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= n; j++)
			cin >> maz[i][j];
	floyd();
	cout << solve() << endl;
	return 0;
}