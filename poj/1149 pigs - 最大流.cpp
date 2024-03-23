#include "iostream"
using namespace std;
#define maxn 500
#define maxm 50005
#define maxhouse 1005
const int INF = 99999999;
int s, t, house, ctm, tot;
int eh[maxn], pre[maxn], cur[maxn], gap[maxn], dist[maxn], a[maxn], hcap[maxhouse];
bool visit[maxhouse];

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

int min(int a, int b) {
	return a < b ? a : b;
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
	memset(a, 0, sizeof(a));
	for(u = 0; u <= n; u++) cur[u] = eh[u];
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
			if(--gap[dist[u]] == 0) break;
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

int main() {
	int i, j, cap, v, nkey;
	memset(visit, false, sizeof(visit));
	cin >> house >> ctm;
	init();
	s = 0, t = ctm + 1;
	for(i = 1; i <= house; i++) {
		cin >> hcap[i];
	}
	for(i = 1; i <= ctm; i++) {
		cin >> nkey;
		for(j = 1; j <= nkey; j++) {
			cin >> v;
			if(!visit[v]) {
				addedge(s, i, hcap[v]);
				visit[v] = true;
				pre[v] = i;
			}
			else addedge(pre[v], i, INF);
		}
		cin >> cap;
		addedge(i, t, cap);
	}
	cout << isap(s, t, t - s + 1) << endl;
	return 0;
}


