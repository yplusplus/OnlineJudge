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

const double eps = 1e-8;
const int N = 55;
const int M = 111111;
const int NN = N * N;
int a[N][N], b[N][N], c[N][N];
int eh[NN], tot;
int dist[NN], cur[NN];
int n, m;

struct Edge {
    int v, next;
    double cap, flow;
} et[M];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void add(int u, int v, double cap, double flow) {
    et[tot].v = v;
    et[tot].cap = cap;
    et[tot].flow = flow;
    et[tot].next = eh[u];
    eh[u] = tot++;
}

void addedge(int u, int v, double cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
}

bool bfs(int s, int t) {
    queue<int> que;
    memset(dist, -1, sizeof(dist));
    dist[s] = 0;
    que.push(s);
    while (!que.empty() && dist[t] == -1) {
        int u = que.front();
        que.pop();
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            if (dist[v] == -1 && et[i].cap > et[i].flow) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
    return dist[t] != -1;
}

double dfs(int u, int t, double d) {
    if (u == t) return d;
    double l = d, ret = 0.0;
    for (int &i = cur[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (et[i].cap > et[i].flow && dist[u] + 1 == dist[v]) {
            double tmp = dfs(v, t, min(l, et[i].cap - et[i].flow));
            l -= tmp;
            et[i].flow += tmp;
            et[i ^ 1].flow -= tmp;
            ret += tmp;
            if (l < eps) break;
        }
    }
    return ret;
    //return d - l;
}

double Dinic(int s, int t, double mid) {
    double res = 0;
    while (bfs(s, t)) {
        memcpy(cur, eh, sizeof(eh));
        res += dfs(s, t, n * m * 100.0);
    }
    return res;
}

int getId(int x, int y) {
    return x * (m + 2) + y;
}

bool check(double mid) {
    double sum = 0;
    init();
    int s = NN - 2, t = NN - 1;
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            if (i == 0 || i == n + 1 || j == 0 || j == m + 1) {
                addedge(getId(i, j), t, dinf);
            } else {
                addedge(s, getId(i, j), a[i][j]);
                sum += a[i][j];
            }
        }
    }
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= m; j++) {
            addedge(getId(i, j), getId(i - 1, j), mid * b[i][j]);
            addedge(getId(i - 1, j), getId(i, j), mid * b[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + 1; j++) {
            addedge(getId(i, j), getId(i, j - 1), mid * c[i][j]);
            addedge(getId(i, j - 1), getId(i, j), mid * c[i][j]);
        }
    }
    return sum > Dinic(s, t, mid);
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &b[i][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m + 1; j++) {
                scanf("%d", &c[i][j]);
            }
        }
        double l = 0, r = n * m * 30;
        while (l + 1e-6 < r) {
            double mid = (l + r) / 2.0;
            if (check(mid)) l = mid;
            else r = mid;
        }
        printf("%.3f\n", (l + r) / 2.0);
    }
    return 0;
}
