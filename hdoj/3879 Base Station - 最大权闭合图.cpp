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
const int N = 55555;
const int M = 999999;
int eh[N], tot, cur[N];
int dist[N];
int n, m, s, t;
int cost[N];
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
        for(int i = 0; i <= n + m + 1; i++) cur[i] = eh[i];
        flow += dfs(s, inf);
    }
    return flow;
}
int main() {
    while(~scanf("%d%d", &n, &m)) {
        int sum = 0;
        init();
        s = 0, t = n + m + 1;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &cost[i]);
            addedge(i, t, cost[i]);
        }
        for(int i = 1; i <= m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            sum += c;
            addedge(s, n + i, c);
            addedge(n + i, a, inf);
            addedge(n + i, b, inf);
        }
        sum -= Dinic();
        printf("%d\n", sum);
    }
    return 0;
}
