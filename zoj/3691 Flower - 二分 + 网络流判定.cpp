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
const int N = 333;
const int M = N * N;
ll dis[N][N];
int sum;
int s, t;
int n;
int eh[N], tot;
int cur[N], que[N];
int dist[N];
struct Edge {
    int u, v, cap, flow, next;
}et[M];

struct Node {
    int x, y, z, f, l;
}node[N];

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
int dfs(int u, int d) {
    if(u == t) return d;
    int l = d;
    for(int &i = cur[u]; i != -1; i = et[i].next) {//当前弧优化
        if(et[i].cap > et[i].flow && dist[u] == dist[et[i].v] + 1) {
            int tmp = dfs(et[i].v, min(et[i].cap - et[i].flow, l)); 
            et[i].flow += tmp;
            et[i^1].flow -= tmp;
            l -= tmp;
            if(l == 0) break;
        }
    }
    return d - l;
}
int Dinic() {
    int flow = 0;
    while(bfs()) {
        for(int i = 0; i <= 2 * n + 1; i++) cur[i] = eh[i];
        flow += dfs(s, inf);
    }
    return flow;
}

ll sq(ll x) {
    return x * x;
}

ll getDist(Node a, Node b) {
    return sq(a.x - b.x) + sq(a.y - b.y) + sq(a.z - b.z);
}

void build(ll limit) {
    init();
    s = 0;
    t = 1;
    for (int i = 2; i <= n; i++) {
        addedge(i, i + n, node[i].l);
        addedge(s, i, node[i].f);
        for (int j = 1; j <= n; j++) {
            if (dis[i][j] <= limit) {
                addedge(i + n, j, inf);
            }
        }
    }
}

bool check(ll limit) {
    build(limit);
    return (sum - node[1].f == Dinic());
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dis[i][j] = linf;
            else dis[i][j] = getDist(node[i], node[j]);
        }
    }
    ll ans = -1;
    ll l = 0, r = 1LL << 40;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    if (ans < 0) puts("-1");
    else printf("%.15f\n", sqrt((double)ans));
}

int main() {
    while (cin >> n) {
        sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d%d%d", &node[i].x, &node[i].y, &node[i].z, &node[i].f, &node[i].l);
            sum += node[i].f;
        }
        solve();
    }
    return 0;
}
