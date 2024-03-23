#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 105
#define maxm 100005
const int INF = 99999999;
int s, t;
int n, m;
int dist[maxn], low[maxn], tot, eh[maxn], pre[maxn], cnt[maxn], cur[maxn];
int maz[maxn][maxn], map[maxn][maxn];

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

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

int isap(int s, int t, int n) {
	int u, v, now;
	memset(dist, 0, sizeof(dist));
	memset(low, 0, sizeof(low));
	for(u = 0; u <= n; u++) cur[u] = eh[u];
	int maxflow = 0;
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
				low[s] = INF;
				maxflow += low[t];
			}
		} else {
			if(--cnt[dist[u]] == 0) break;
			dist[u] = n;
			cur[u] = eh[u];
			for(now = eh[u]; now != -1; now = et[now].next)
				if(et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1) 
					dist[u] = dist[et[now].v] + 1;
			cnt[dist[u]]++;
			if(u != s) u =et[pre[u]].u;
		}
	}
	return maxflow;
}

void floyd() {
	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			if(maz[i][k] != -1)
				for(int j = 0; j < n; j++)
					if(maz[k][j] != -1)
						if(maz[i][j] == -1) maz[i][j] = maz[i][k] + maz[k][j];
						else maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
}

void build() {
	init();
	for(int i = 0; i < n; i++)
		if(maz[s][i] != -1)
			for(int j = 0; j < n; j++)
				if(maz[j][t] != -1)
					if(i != j && map[i][j] != -1 && maz[s][i] + map[i][j] + maz[j][t] == maz[s][t])
						addedge(i, j, 1);
}

int main() {
	while(cin >> n) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				cin >> maz[i][j];
				if(i == j) maz[i][j] = 0;	//没有这句就wa,不知道什么原因,是输入的时候不保证 maz[i][i] == 0 ???
				map[i][j] = maz[i][j];
			}
		}
		cin >> s >> t;
		if(s == t)
			cout << "inf" << endl;
		else {
			floyd();
			build();
			cout << isap(s, t, n) << endl;
		}
	}
	return 0;
}