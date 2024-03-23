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
#define maxn 11000
#define maxm 50000
const int inf = 1 << 29;
int n, m, s, t;
int eh[maxn], low[maxn], dist[maxn], pre[maxn], cur[maxn], tot, cnt[maxn];
int val[110];
int acnt, bcnt, num;
struct Briage {
    int u, v, w, p;
    Briage(){}
    Briage(int _u, int _v, int _w) {
        u = _u, v = _v, w = _w;
    }
    Briage(int _u, int _v, int _w, int _p) {
        u = _u, v = _v, w = _w, p = _p;
    }
}b[15], a[maxm];

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

void solve() {
//    cout << acnt << " " << bcnt << endl;
    int ans = 0, anscost = inf;
    s = 0, t = num + n + 1;
    for(int i = 0; i < (1 << bcnt); i++) {
        init();
        int id = 0;
        for(int j = 1; j <= n; j++)
            if(val[j]) addedge(s, j, val[j]);
        for(int j = 0; j < acnt; j++) {
            if(a[j].p == 0) addedge(a[j].u, a[j].v, inf);
            else {
                id++;
                addedge(a[j].u, n + id, inf);
                addedge(n + id, a[j].v, inf);
                addedge(n + id, t, a[j].w);
            }
        }
        int res = 0;
        for(int j = 0; j < bcnt; j++) {
            if(i & (1 << j)) {
                res += b[j].w;
                addedge(b[j].u, b[j].v, inf);
            } else addedge(b[j].u, b[j].v, 1);
        }
        int flow = isap(s, t, t - s + 1);
      //  cout << flow << " " << res << endl;
        if(flow > ans) ans = flow, anscost = res;
        else if(flow == ans && res < anscost) anscost = res;

    }
    if(ans == 0) puts("Poor Heaven Empire");
    else printf("%d %d\n", ans, anscost);
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
        bcnt = acnt = num = 0;
        for(int i = 0; i < m; i++) {
            int u, v, w, p;
            scanf("%d%d%d%d", &u, &v, &w, &p);
            if(p <= 0) {
                if(p < 0) num++;
                a[acnt++] = Briage(u, v, w, p);
            } else b[bcnt++] = Briage(u, v, w);
        }
        solve();
    }
    return 0;
}

