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
const int N = 55;
const int M = 11111;
int eh[N], tot, cur[N];
int dist[N];
int n, m, s, t;
int cost[N];
int in[N], out[N];
pii g[M];
struct Edge {
    int u, v, cap, flow, next;
}et[M];
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
        for(int i = 0; i <= n + 3; i++) cur[i] = eh[i];
        flow += dfs(s, inf);
    }
    return flow;
}
bool calc(int mid) {
    int sum = 0;
    init();
    addedge(n + 1, 0, mid);
    for(int i = 0; i <= n + 1; i++) {
        int delta = in[i] - out[i];
        if(delta > 0) {
            sum += delta;
            addedge(s, i, delta);
        } else {
            addedge(i, t, -delta);
        }
    }
    for(int i = 0; i < m; i++) {
        addedge(g[i].fi, g[i].se, inf);
    }
    return sum == Dinic();
}
int main() {
    char from[5], to[5];
    while(~scanf("%d%d", &n, &m)) {
        if(!n && !m) break;
        s = n + 2, t = n + 3;
        int a, b, c;
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        for(int i = 0; i < m; i++) {
            scanf("%s%s%d", from, to, &c);
            if(from[0] == '+') a = 0;
            else sscanf(from, "%d", &a);
            if(to[0] == '-') b = n + 1;
            else sscanf(to, "%d", &b);
            g[i] = mp(a, b);
            out[a] += c;
            in[b] += c;
        }
        int ans = -1, l = 0, r = 1 << 20;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(calc(mid)) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        if(ans == -1) puts("impossible");
        else printf("%d\n", ans);
    }
    return 0;
}
