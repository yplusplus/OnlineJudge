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
const double eps = 1e-10;
const int N = 111;
const int M = 111111;
int n, m, p;
int eh[N], tot;

struct Edge {
    int u, v;
    double flow, cap;
    int next;
} et[M];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void add(int u, int v, double flow, double cap) {
    Edge e = {u, v, flow, cap, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void addedge(int u, int v, double cap) {
    add(u, v, 0, cap), add(v, u, 0, 0);
}

int dist[N], cur[N];
int s, t;
int que[N];
bool bfs() {
    int head = 0, tail = 0;
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

double dfs(int u, double d) {
    if(u == t) return d;
    double l = d;
    for(int &i = cur[u]; i != -1; i = et[i].next) {
        if(et[i].cap > et[i].flow && dist[u] == dist[et[i].v] + 1) {
            double tmp = dfs(et[i].v, min(et[i].cap - et[i].flow, l)); 
            et[i].flow += tmp;
            et[i^1].flow -= tmp;
            l -= tmp;
            if(l == 0) break;
        }
    }
    return d - l;
}
double Dinic() {
    double flow = 0;
    while(bfs()) {
        for(int i = 1; i <= n; i++) cur[i] = eh[i];
        flow += dfs(s, 1e10);
    }
    return flow;
}

pair<pair<int, int>, double> e[M >> 1];
int main() {
    while (~scanf("%d%d%d", &n, &m, &p)) {
        s = 1, t = n;
        init();
        for (int i = 0; i < m; i++) {
            int u, v;
            double w;
            scanf("%d%d%lf", &u, &v, &w);
            addedge(u, v, w);
            e[i] = mp(mp(u, v), w);
        }
        double ans = Dinic();
        double res = -1;
        double l = 0.0, r = 1e10;
        for (int j = 0; j < 70; j++) {
            double mid = (l + r) / 2.0;
            init();
            for (int i = 0; i < m; i++) {
                addedge(e[i].fi.fi, e[i].fi.se, min(e[i].se, mid));
            }
            double tmp = Dinic();
            if (tmp + eps < ans) l = mid + 1;
            else r = mid - 1, res = mid;
        }
        cout << ans << endl;
        printf("%.10f\n", res * p);
    }
    return 0;
}
