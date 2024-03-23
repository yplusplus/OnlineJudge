#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 1444;
const int M = 999999;
int eh[N], tot, cur[N];
int dist[N];
int n, m, s, t;
int in[N], out[N];
int photo[400][1111];
vector<pii> scheme;
struct G {
    int u, v, a, b;
    G(){}
    G(int _u, int _v, int _a, int _b) {
        u = _u, v = _v, a = _a, b = _b;
    }
}g[444444];
int gtot;
struct Edge {
    int v, cap, flow, next;
}et[M];
void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}
void add(int u, int v, int cap, int flow) {
    Edge e = {v, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}
void addedge(int u, int v, int cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
}
bool bfs() {
    int que[N], head = 0, tail = 0;
    memset(dist, -1, sizeof(dist));
    dist[t] = 0;
    que[tail++] = t;
    while(head < tail && dist[s] == -1) {
        int u = que[head++];
        for(int i = eh[u]; i != -1; i = et[i].next) {
            if(et[i^1].cap > et[i^1].flow && dist[et[i].v] == -1) {
                dist[et[i].v] = dist[u] + 1;
                que[tail++] = et[i].v;
            }
        }
    }
    return dist[s] != -1;
}
int dfs(int u, int d) {
    if(u == t) return d;
    int l = d;
    for(int &i = cur[u]; i != -1; i = et[i].next) {
        if(et[i].cap > et[i].flow && dist[et[i].v] + 1 == dist[u]) {
            int tmp = dfs(et[i].v, min(l, et[i].cap - et[i].flow));
            l -= tmp;
            et[i].flow += tmp;
            et[i^1].flow -= tmp;
            if(l == 0) break;
        }
    }
    return d - l;
}
int Dinic() {
    int flow = 0;
    while(bfs()) {
        for(int i = 0; i <= n + m + 3; i++) cur[i] = eh[i];
        flow += dfs(s, inf);
    }
    return flow;
}
bool calc(int mid) {
    int sum = 0;
    init();
    for(int i = 0; i <= n + m + 1; i++) {
        in[i] = out[i] = 0;
    }
    g[gtot] = G(n + m + 1, 0, mid, inf);
    for(int i = 0; i <= gtot; i++) {
        int u = g[i].u, v = g[i].v, a = g[i].a, b = g[i].b;
        out[u] += a;
        in[v] += a;
        addedge(u, v, b - a);
    }
    for(int i = 0; i <= n + m + 1; i++) {
        int delta = in[i] - out[i];
        if(delta > 0) {
            sum += delta;
            addedge(s, i, delta);
        } else addedge(i, t, -delta);
    }
    return sum == Dinic();
}
void solve() {
    s = n + m + 2, t = n + m + 3;
    int l = 0, r = 12222222, ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(calc(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    if(ans == -1) printf("-1\n\n");
    else {
        calc(ans);
        for(int i = 1; i <= n; i++) {
            for(int j = eh[i]; j != -1; j = et[j].next) {
                if(et[j].v >= n + 1 && et[j].v <= n + m) {
                    photo[i][et[j].v - n] += et[j].flow;
                }
            }
        }
        printf("%d\n", ans);
        for(int i = 0; i < scheme.size(); i++) {
            printf("%d\n", photo[scheme[i].fi][scheme[i].se]);
        }
        puts("");
    }
}
int main() {
    while(~scanf("%d%d", &n, &m)) {
        gtot = 0;
        memset(photo, 0, sizeof(photo));
        scheme.clear();
        for(int i = 1; i <= m; i++) {
            int gi;
            scanf("%d", &gi);
            g[gtot++] = G(n + i, n + m + 1, gi, inf);
        }
        for(int i = 1; i <= n; i++) {
            int ci, di;
            scanf("%d%d", &ci, &di);
            g[gtot++] = G(0, i, 0, di);
            for(int j = 0; j < ci; j++) {
                int target, l, r;
                scanf("%d%d%d", &target, &l, &r);
                target++;
                g[gtot++] = G(i, target + n, l, r);
                photo[i][target] += l;
                scheme.pb(mp(i, target));
            }
        }
        solve();
    }
    return 0;
}
