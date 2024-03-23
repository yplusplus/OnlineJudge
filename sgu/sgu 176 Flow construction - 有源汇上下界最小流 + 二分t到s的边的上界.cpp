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
const int inf = 1000000000;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 111;
int eh[N], tot, cur[N];
int in[N], out[N];
int dist[N];
int n, m, s, t;
int cap[N][N], flow[N][N];
struct Edge {
    int u, v, a, b;
    Edge(){}
    Edge(int _u, int _v, int _a, int _b) {
        u = _u, v = _v, a = _a, b = _b;
    }
}graph[N*N];
bool bfs() {
    int que[N], head = 0, tail = 0;
    memset(dist, -1, sizeof(dist));
    dist[t] = 0;
    que[tail++] = t;
    while(head < tail && dist[s] == -1) {
        int u = que[head++];
        for(int v = 0; v <= n + 1; v++) {
            if(cap[v][u] > flow[v][u] && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que[tail++] = v;
            }
        }
    }
    return dist[s] != -1;
}
int dfs(int u, int d) {
    if(u == t) return d;
    int l = d;
    for(int &v = cur[u]; v <= n + 1; v++) {
        if(cap[u][v] > flow[u][v] && dist[v] + 1 == dist[u]) {
            int tmp = dfs(v, min(l, cap[u][v] - flow[u][v]));
            l -= tmp;
            flow[u][v] += tmp;
            flow[v][u] -= tmp;
            if(l == 0) break;
        }
    }
    return d - l;
}
int Dinic() {
    int flow = 0;
    while(bfs()) {
        memset(cur, 0, sizeof(cur));
        flow += dfs(s, inf);
    }
    return flow;
}
bool calc(int mid) {
    s = 0, t = n + 1;
    graph[m] = Edge(n, 1, 0, mid);
    int sum = 0;
    memset(cap, 0, sizeof(cap));
    memset(flow, 0, sizeof(flow));
    for(int i = 0; i <= m; i++) {
        int delta = graph[i].b - graph[i].a;
        cap[graph[i].u][graph[i].v] += delta;
    }
    for(int i = 1; i <= n; i++) {
        int delta = in[i] - out[i];
        if(delta > 0) {
            sum += delta;
            cap[s][i] += delta;
        } else {
            cap[i][t] += -delta;
        }
    }
    return Dinic() == sum;
}
int main() {
    while(~scanf("%d%d", &n, &m)) {
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        for(int i = 0; i < m; i++) {
            int u, v, a, b;
            scanf("%d%d%d%d", &u, &v, &b, &a);
            if(a) a = b;
            graph[i] = Edge(u, v, a, b);
            out[u] += a;
            in[v] += a;
        }
        int l = 0, r = inf, ans = -1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(calc(mid)) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        if(ans == -1) puts("Impossible");
        else {
            printf("%d\n", ans);
            calc(ans);
            for(int i = 0; i < m; i++) {
                if(graph[i].a == graph[i].b) printf("%d%c", graph[i].a, i == m - 1 ? '\n' : ' ');
                else printf("%d%c", flow[graph[i].u][graph[i].v], i == m - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
