#include "iostream"
#include "cstdio"
#include "vector"
#include "queue"
using namespace std;
#define maxn 505
#define maxm 50005
const int INF = 99999999;
int n, m, s, t;
int eh[maxn], pre[maxn], cur[maxn], dist[maxn], cnt[maxn], color[maxn], tot, low[maxn], ans;
vector<int> vecs[maxn], vect[maxn];
queue<int> que;
struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

void init() {
	tot = ans = 0;
	memset(eh, -1, sizeof(eh));
	memset(color, 0, sizeof(color));
}

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

void isap(int s, int t, int n) {
	int u, v, now, flow = 0;
	memset(dist, 0, sizeof(dist));
	memset(low, 0, sizeof(low));
	memset(cnt, 0, sizeof(cnt));
	for(u = 0; u <= n; u++) cur[u] = eh[u];
	low[s] = INF, cnt[0] = n;
	u = s;
	while(dist[s] < n) {
		for(now = cur[u]; now != -1; now = et[now].next) {
			if(et[now].cap - et[now].flow && dist[u] == dist[v = et[now].v] + 1) break;
		}
		if(now != -1) {
			cur[u] = pre[v] = now;
			low[v] = min(low[u], et[now].cap - et[now].flow);
			u = v;
			if(u == t) {
				for(; u != s; u = et[pre[u]].u) {
					et[pre[u]].flow += low[t];
					et[pre[u]^1].flow -= low[t];
				}
				low[s] = INF, flow += low[t];
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
}

void dfs1(int u) {
	color[u] = 1;
	int size = vecs[u].size();
	for(int i = 0; i < size; i++) {
		int v = vecs[u][i];
		if(!color[v]) dfs1(v);
	}
}

void dfs2(int u) {
	color[u] = 2;
	int size = vect[u].size();
	for(int i = 0; i < size; i++) {
		int v = vect[u][i];
		if(!color[v]) dfs2(v);
	}
}

int main() {
	int i, u, v, cap;
	scanf("%d%d", &n, &m);
	init();
	for(i = 0; i < m; i++) {
		scanf("%d%d%d", &u, &v, &cap);
		if(cap) addedge(u, v, cap);
	}
	s = 0, t = n - 1;
	isap(s, t, n);
	for(i = 0; i < maxn; i++) vecs[i].clear(), vect[i].clear();
	for(i = 0; i < tot; i += 2) {
		if(et[i].cap - et[i].flow) {
			u = et[i].u, v = et[i].v;
			vecs[u].push_back(v);
			vect[v].push_back(u);
		} else que.push(i);
	}
	dfs1(s), dfs2(t);
	while(!que.empty()) {
		i = que.front();
		que.pop();
		u = et[i].u, v = et[i].v;
		if(color[u] == 1 && color[v] == 2) ans++;
	}
	cout << ans << endl;
	return 0;
}