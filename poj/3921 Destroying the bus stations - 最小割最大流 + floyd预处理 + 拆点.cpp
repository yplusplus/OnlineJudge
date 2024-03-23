#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 1050
#define maxm 1000050
const int inf = 1 << 30;
int maz[55][55];
int n, m, k;
int s, t;

int eh[maxn], low[maxn], dist[maxn], pre[maxn], cur[maxn], tot, cnt[maxn];

struct Edge {
	int u, v, cap, flow, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

void floyd() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(maz[i][k] != inf && maz[k][j] != inf)
                    maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
            }
        }
    }
}

int isap(int s, int t, int n){
	int u, v, now, flow = 0;
	memset(dist, 0, sizeof(dist)); 
	memset(low, 0, sizeof(low));
	memset(cnt, 0, sizeof(cnt));
	for(u = 0 ; u <= n ; u ++) cur[u] = eh[u];
	low[s] = inf, cnt[0] = n, u = s;
	while(dist[s] < n) {
		for(now = cur[u]; now != -1; now = et[now].next)
			if(et[now].cap - et[now].flow && dist[u] == dist[ v = et[now].v ] + 1 ) break;
		if(now != -1) {
			cur[u] = pre[v] = now;
			low[v] = min(et[now].cap - et[now].flow, low[u]);
			u = v;
			if(u == t) {
				for(; u != s; u = et[pre[u]].u){
					et[pre[u]].flow += low[t];
					et[pre[u]^1].flow -= low[t];
				}
				flow += low[t]; low[s] = inf;
			}
		} else {
			if(--cnt[dist[u]] == 0) break;
			dist[u] = n, cur[u] = eh[u];
			for(now = eh[u]; now != -1; now = et[now].next)
				if(et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1)
					dist[u] = dist[ et[now].v ] + 1;
			cnt[dist[u]]++;
			if(u != s) u = et[pre[u]].u;
		}
	}
	return flow;
}

int main() {
    int u, v;
    while(~scanf("%d%d%d", &n, &m, &k)) {
        if(!n) break;
        s = 1, t = n;
        init();
        for(int i = 0; i < 55; i++)
            for(int j = 0; j < 55; j++)
                maz[i][j] = inf;
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            maz[u][v] = 1;
        }
        floyd();
        for(int i = 2; i < n; i++) {
            if(maz[s][i] + maz[i][t] <= k) {
                addedge(i, i + n, 1);
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(maz[i][j] == 1) addedge(i + n, j, inf);
            }
        }
        int ans = isap(s + n, t, 2 * n - 2);
        cout << ans << endl;
    }
    return 0;
}
