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
const int M = 99999;
int eh[N], tot;
int dist[N];
int que[N], cur[N];
int s, t, n, np, nc, m;
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
    int head = 0, tail = 0;
    memset(dist, -1, sizeof(dist));
    dist[s] = 0;
    que[tail++] = s;
    while (head < tail && dist[t] == -1) {
        int u = que[head++];
        for (int i = eh[u]; i != -1; i = et[i].next) {
            if (et[i].cap > et[i].flow && dist[et[i].v] == -1) {
                dist[et[i].v] = dist[u] + 1;
                que[tail++] = et[i].v;
            }
        }
    }
    return dist[t] != -1;
}

int dfs(int u, int d) {
    if (u == t) return d;
    int l = d;
    for (int &i = cur[u]; i != -1; i = et[i].next) {
        if (et[i].cap > et[i].flow && dist[u] + 1 == dist[et[i].v]) {
            int tmp = dfs(et[i].v, min(et[i].cap - et[i].flow, l));
            et[i].flow += tmp;
            et[i^1].flow -= tmp;
            l -= tmp;
            if (l == 0) break;
        }
    }
    return d - l;
}

int Dinic() {
    int flow = 0;
    while (bfs()) {
        for (int i = 0; i < n + 5; i++) cur[i] = eh[i];
        flow += dfs(s, inf);
    }
    return flow;
}

inline void readEdge(int &u, int &v, int &cap) {
    char ch;
    while ((ch = getchar()) != '(') ;
    scanf("%d,%d)%d", &u, &v, &cap);
}

inline void readNode(int &u, int &z) {
    char ch;
    while ((ch = getchar()) != '(') ;
    scanf("%d)%d", &u, &z);
}

int main() {
    while (~scanf("%d%d%d%d", &n, &np, &nc, &m)) {
        init();
        s = n, t = s + 1;
        for (int i = 0; i < m; i++) {
            int u, v, cap;
            readEdge(u, v, cap);
            if (u != v) addedge(u, v, cap);
        }
        for (int i = 0; i < np; i++) {
            int u, z;
            readNode(u, z);
            addedge(s, u, z);
        }
        for (int i = 0; i < nc; i++) {
            int u, z;
            readNode(u, z);
            addedge(u, t, z);
        }
        int ans = 0;
        if (np && nc) ans = Dinic();
        printf("%d\n", ans);
    }
    return 0;
}
