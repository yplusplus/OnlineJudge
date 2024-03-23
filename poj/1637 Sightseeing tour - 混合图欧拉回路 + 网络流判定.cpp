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
#define maxn 210
#define maxm 10050
typedef pair<int, int> pii;
const int inf = 1 << 30;
int in[maxn], out[maxn];
int n, m, s, t;
int eh[maxn], low[maxn], dist[maxn], pre[maxn], cur[maxn], tot, cnt[maxn];
vector<pii> vec;
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

bool solve() {
    for(int i = 1; i <= n; i++)
        if((in[i] - out[i]) % 2 != 0) return false;
    for(int i = 1; i <= n; i++) {
        if(in[i] >= out[i]) addedge(i, t, (in[i] - out[i]) / 2);
        else addedge(s, i, (out[i] - in[i]) / 2);
    }
    int flow = isap(s, t, n + 2);
    for(int i = eh[s]; i != -1; i = et[i].next) {
        if(et[i].cap != et[i].flow) return false;
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        init();
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(in));
        scanf("%d%d", &n, &m);
        s = 0, t = n + 1;
        int a, b, c;
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &a, &b, &c);
            out[a]++, in[b]++;
            if(!c) addedge(a, b, 1);
        }
        if(solve()) printf("possible\n");
        else printf("impossible\n");
    }
    return 0;
}
