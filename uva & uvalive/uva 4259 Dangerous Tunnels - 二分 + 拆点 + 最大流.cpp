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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 1000
#define maxm 500000
const int inf = 1 << 30;
int n, m, s, t, nn, k;
int eh[maxn], low[maxn], dist[maxn], pre[maxn], cur[maxn], tot, cnt[maxn];
int road[maxm][3];
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

void build(int limit) {
    init();
    for(int i = 0; i < nn; i++) {
        addedge(i, i + nn, 1);
    }
    for(int i = 0; i < m; i++) {
        if(road[i][2] <= limit) addedge(road[i][0] + nn, road[i][1], 1);
    }
}
void solve() {
    int l = 1, r = 200000;
    int ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        build(mid);
        if(isap(0 + nn, n + 1, nn * 2) >= k) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    if(ans == -1) puts("no solution");
    else printf("%d\n", ans);
}

int main() {
    int Case = 1;
    while(~scanf("%d", &n), n) {
        nn = n + 2;
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            if(u > v) swap(u, v);
            road[i][0] = u, road[i][1] = v, road[i][2] = w;
        }
        scanf("%d", &k);
        printf("Case %d: ", Case++);
        solve();
    }
    return 0;
}
