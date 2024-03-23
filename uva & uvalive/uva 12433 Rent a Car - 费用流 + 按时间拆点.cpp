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
const int N = 111;
const int M = 222222;
int need[N];
int n, C, R;
int c[N], p[N], d[N], s[N];

struct CostFLow {
    int s, t;
    int ans, anscost;
    int eh[N], tot;
    int pre[N], dist[N], low[N];
    bool visit[N];
    struct Edge {
        int u, v, cost, cap, flow, next;
    } et[M];
    void init() {
        memset(eh, -1, sizeof(eh));
        tot = 0;
    }
    void add(int u, int v, int cost, int cap, int flow) {
        Edge e = {u, v, cost, cap, flow, eh[u]};
        et[tot] = e;
        eh[u] = tot++;
    }
    void addedge(int u, int v, int cost, int cap) {
        add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
    }
    bool findPath() {
        for (int i = 0; i < N; i++) {
            pre[i] = -1;
            visit[i] = false;
            dist[i] = inf;
            low[i] = 0;
        }
        queue<int> que;
        que.push(s);
        dist[s] = 0;
        low[s] = inf;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            visit[u] = false;
            for (int i = eh[u]; ~i; i = et[i].next) {
                int v = et[i].v;
                if (et[i].cap > et[i].flow && dist[v] > dist[u] + et[i].cost) {
                    dist[v] = dist[u] + et[i].cost;
                    pre[v] = i;
                    low[v] = min(low[u], et[i].cap - et[i].flow);
                    if (!visit[v]) {
                        visit[v] = true;
                        que.push(v);
                    }
                }
            }
        }
        //cout << "dist = " << dist[t] << endl;
        return dist[t] != inf;
    }
    void solve() {
        ans = anscost = 0;
        while (findPath()) {
            //cout << dist[t] << " " << low[t] << endl;
            ans += low[t];
            anscost += low[t] * dist[t];
            int x = pre[t];
            while (~x) {
                et[x].flow += low[t];
                et[x ^ 1].flow -= low[t];
                x = pre[et[x].u];
            }
        }
    }
} costflow;

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &C, &R);
        costflow.init();
        costflow.s = 0, costflow.t = 2 * n + 2;
        int v = 2 * n + 1;
        int sum = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &need[i]), sum += need[i];
        for (int i = 0; i < C; i++) {
            scanf("%d%d", &c[i], &p[i]);
        }
        for (int i = 0; i < R; i++) {
            scanf("%d%d", &d[i], &s[i]);
        }
        for (int i = 1; i <= n; i++) {
            costflow.addedge(0, i, 0, need[i]);
            costflow.addedge(i + n, 2 * n + 2, 0, need[i]);
            if (i + 1 <= n) costflow.addedge(i + n, i + 1 + n, 0, inf);
            for (int j = 0; j < R; j++) {
                if (i + d[j] + 1 <= n) costflow.addedge(i, i + d[j] + 1 + n, s[j], inf);
            }
        }
        for (int i = 0; i < C; i++) {
            costflow.addedge(0, v, p[i], c[i]);
        }
        costflow.addedge(v, n + 1, 0, inf);
        costflow.solve();
        //cout << costflow.ans << " " << costflow.anscost << endl;
        printf("Case %d: ", Case++);
        if (costflow.ans == sum) printf("%d\n", costflow.anscost);
        else puts("impossible");
    }
    return 0;
}
