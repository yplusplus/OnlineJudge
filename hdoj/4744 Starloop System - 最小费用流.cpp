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

int now_dist;
struct Point {
    int x, y, z, w;
    void read() {
        scanf("%d%d%d%d", &x, &y, &z, &w);
    }
} point[111];

const int N = 222;
const int M = N * N * N;
int eh[N], tot, cur[N];
int dist[N];
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

bool spfa(int s, int t) {
    queue<int> que;
    for (int i = 0; i <= t; i++) { dist[i] = inf; }
    dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, w = et[i].cost;
            if (et[i].cap > et[i].flow && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    now_dist = dist[t];
    return dist[t] != inf;
}

bool modify_label(int n) {
    int d = inf;
    for (int u = 0; u < n; u++) 
        if (visit[u]) {
            for (int j = eh[u]; ~j; j = et[j].next) {
                int v = et[j].v;
                if (et[j].cap > et[j].flow && !visit[v]) d = min(d, dist[u] + et[j].cost - dist[v]);
            }
        }
    if (d == inf) return false;
    for (int u = 0; u < n; u++) if (visit[u]) dist[u] -= d;
    now_dist += d;
    return true;
}

int flow, cost;
int dfs(int u, int t, int d) {
    if (t == u) { return cost += d * now_dist, flow += d, d; }
    int l = d;
    visit[u] = true;
    for (int i = eh[u]; ~i; i = et[i].next) {
        int v = et[i].v;
        if (!visit[v] && dist[v] == dist[u] + et[i].cost && et[i].cap > et[i].flow) {
            int tmp = dfs(v, t, min(et[i].cap - et[i].flow, l));
            et[i].flow += tmp;
            et[i ^ 1].flow -= tmp;
            l -= tmp;
            if (l == 0) break;
        }
    }
    return d - l;
}

void mcmf(int s, int t) {
    flow = cost = 0;
    spfa(s, t);
    int tmp;
    do {
        do {
            memset(visit, false, sizeof(visit));
        } while (dfs(s, t, inf));
    } while (modify_label(t + 1));
}

double sqr(double x) { return x * x; }
int get_dist(const Point &a, const Point &b) {
    return (int) floor(sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z)));
}

int main() {
    int n;
    while (~scanf("%d", &n), n) {
        for (int i = 1; i <= n; i++) point[i].read();
        int s = 0, t = 2 * n + 1;
        int sum = 0;
        init();
        for (int i = 1; i <= n; i++) {
            sum += point[i].w;
            addedge(s, i, 0, point[i].w);
            addedge(i + n, t, 0, point[i].w);
            for (int j = 1; j < i; j++) {
                int cost = get_dist(point[i], point[j]);
                addedge(i, j + n, cost, inf);
                addedge(j, i + n, cost, inf);
            }
        }
        mcmf(s, t);
        if (sum == flow) printf("%d\n", cost);
        else puts("-1");
    }
    return 0;
}
