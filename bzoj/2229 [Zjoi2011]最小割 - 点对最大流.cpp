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

const int N = 155;
int eh[N], tot, cur[N];
int dist[N];
int n, m;
int fa[N];
struct Edge {
    int v, cap, flow, next;
} et[N * N];

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
    add(u, v, cap, 0), add(v, u, cap, 0);
}

bool bfs(int s, int t) {
    memset(dist, -1, sizeof(dist));
    int que[N], head = 0, tail = 0;
    que[tail++] = s;
    dist[s] = 0;
    while (head < tail) {
        int u = que[head++];
        for (int i = eh[u]; ~i; i = et[i].next) {
            int v = et[i].v;
            if (dist[v] == -1 && et[i].cap > et[i].flow) {
                dist[v] = dist[u] + 1;
                que[tail++] = v;
            }
        }
    }
    //cout << dist[t] << endl;
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
            if ((l -= tmp) == 0) break;
        }
    }
    return d - l;
}

int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        memcpy(cur, eh, sizeof(eh));
        flow += dfs(s, t, inf);
    }
    return flow;
}

int ans[N][N];

void solve() {
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) ans[i][j] = inf;
    memset(fa, 0, sizeof(fa));
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < tot; j++) et[j].flow = 0;
        int ret = dinic(i, fa[i]);
        ans[i][fa[i]] = ans[fa[i]][i] = ret;
        //cout << ret << endl;
        for (int j = i + 1; j < n; j++) {
            if (dist[j] != -1 && fa[j] == fa[i]) fa[j] = i;
        }
        for (int j = 0; j < i; j++) {
            ans[i][j] = ans[j][i] = min(ret, ans[j][fa[i]]);
        }
    }
    for (int i = 0; i < n; i++) ans[i][i] = 0;
    //for (int i = 0; i < n; i++) {
        //for (int j = 0; j < n; j++) {
            //cout << ans[i][j] << " " ;
        //}
        //cout << endl;
    //}
    int q, x;
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &x);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                cnt += ans[i][j] <= x;
            }
        }
        printf("%d\n", cnt);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        init();
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            a--, b--;
            addedge(a, b, c);
        }
        solve();
        if (T) puts("");
    }
    return 0;
}
