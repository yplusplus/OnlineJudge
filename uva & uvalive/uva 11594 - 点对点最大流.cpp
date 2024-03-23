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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 222;
const int M = N * N * N;
struct maxFlowSolver {
    int eh[N], tot, cur[N];
    int maxFlow;
    int dist[N];
    struct Edge {
        int v, cap, flow, next;
    } et[M];
    void init() {
        memset(eh, -1, sizeof(eh));
        tot = 0;
    }
    void add(int u, int v, int cap, int flow) {
        Edge e = {v, cap, flow, eh[u]};
        et[tot] = e;
        eh[u] = tot++;
    }
    void addedge(int u, int v, int cap) {
        add(u, v, cap, 0), add(v, u, 0, 0);
    }
    bool bfs(int s, int t) {
        memset(dist, -1, sizeof(dist));
        queue<int> que;
        que.push(s);
        dist[s] = 0;
        while (!que.empty()) {
            int u = que.front(); que.pop();
            for (int i = eh[u]; ~i; i = et[i].next) {
                int v = et[i].v;
                if (dist[v] == -1 && et[i].cap > et[i].flow) {
                    dist[v] = dist[u] + 1;
                    que.push(v);
                }
            }
        }
        return dist[t] != -1;
    }
    int dfs(int u, int t, int d) {
        if (u == t) return d;
        int l = d;
        for (int &i = cur[u]; ~i; i = et[i].next) {
            int v = et[i].v;
            if (dist[v] == dist[u] + 1 && et[i].cap > et[i].flow) {
                int tmp = dfs(v, t, min(l, et[i].cap - et[i].flow));
                et[i].flow += tmp;
                et[i ^ 1].flow -= tmp;
                l -= tmp;
                if (l == 0) break;
            }
        }
        return d - l;
    }
    int run(int s, int t) {
        maxFlow = 0;
        while (bfs(s, t)) {
           memcpy(cur, eh, sizeof(eh));
           maxFlow += dfs(s, t, inf);
        }
        return maxFlow;
    }
} dinic;

int maz[N][N];
int ans[N][N];
int fa[N];
int n;
void solve() {
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) ans[i][j] = inf;
    memset(fa, 0, sizeof(fa));
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < dinic.tot; j += 2) {
            dinic.et[j].flow += dinic.et[j ^ 1].flow;
            dinic.et[j ^ 1].flow = 0;
        }
        int ret = dinic.run(i, fa[i]);
        ans[i][fa[i]] = ans[fa[i]][i] = ret;
        for (int j = i + 1; j < n; j++) {
            if (dinic.dist[j] != -1 && fa[j] == fa[i]) fa[j] = i;
        }
        for (int j = 0; j < i; j++) {
            ans[i][j] = ans[j][i] = min(ret, ans[fa[i]][j]);
        }
    }
    for (int i = 0; i < n; i++) ans[i][i] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%c", ans[i][j], j + 1 == n ? '\n' : ' ');
        }
    }
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        dinic.init();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &maz[i][j]);
                if (maz[i][j]) dinic.addedge(i, j, maz[i][j]);
            }
        }
        printf("Case #%d:\n", Case++);
        solve();
    }
    return 0;
}
