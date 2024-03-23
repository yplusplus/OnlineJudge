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
#define maxn 1550
#define maxm 1000000
const int inf = 1 << 30;
int n, m, s, t, l;
int eh[maxn], low[maxn], dist[maxn], pre[maxn], cur[maxn], tot, cnt[maxn];
pii p[maxn];
int in[maxn], out[maxn];
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

void greedy() {//Ì°ÐÄ³õÊ¼Á÷
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    in[s] = inf;
    sort(p + 1, p + 1 + n);
    for(int i = 1; i <= n; i++) {
        for(int j = eh[p[i].se]; j != -1; j = et[j].next) {
            if(et[j].cap > 0) {
                int dd = min(et[j].cap, in[p[i].se] - out[p[i].se]);
                out[p[i].se] += dd;
                in[et[j].v] += dd;
            }
        }
    }
    memset(in, 0, sizeof(in));
    in[t] = inf;
    for(int i = n; i >= 1; i--) {
        for(int j = eh[p[i].se]; j != -1; j = et[j].next) {
            if(et[j].cap == 0) {
                int k = j ^ 1;
                int u = et[k].u, v = et[k].v;
                if(out[u] > in[u]) {
                    int dd = min(out[u] - in[u], et[k].cap);
                    dd = min(dd, in[v]);
                    in[u] += dd;
                    in[v] -= dd;
                    et[k].flow += dd;
                }
            }
        }
    }
}
int main() {
    int T, u, v, w, level;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &l);
        init();
        for(int i = 1; i <= n; i++) {
            scanf("%d", &level);
            p[i] = mp(level, i);
            if(level == 1) s = i;
            else if(level == l) t = i;
        }
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
        }
        greedy();
        isap(s, t, n);
        for(int i = 0; i < m; i++) {
            printf("%d\n", et[i<<1].flow);
        }
    }
    return 0;
}
