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

const int N = 2222;
const int M = 55555;
int eh[N], tot;
int dist[N], low[N], pre[N];
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
    for (int i = 0; i < N; i++) dist[i] = -inf;
    memset(visit, false, sizeof(visit));
    pre[s] = -1, low[s] = inf, dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, cost = et[i].cost;
            if (et[i].cap - et[i].flow && dist[v] < dist[u] + cost) {
                dist[v] = dist[u] + cost;
                pre[v] = i;
                low[v] = min(low[u], et[i].cap - et[i].flow);
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dist[t] != -inf;
}

pii mcmf(int s, int t) {
    int flow = 0, cost = 0;
    while (spfa(s, t)) {
        flow += low[t];
        cost += low[t] * dist[t];
        int x = pre[t];
        while (x != -1) {
            et[x].flow += low[t];
            et[x ^ 1].flow -= low[t];
            x = pre[et[x].u];
        }
    }
    return mp(flow, cost);
}

int Sqr[1111 * 1111];
bool check(int a, int b) {
    //if (a == b) return false;
    if (a < b) swap(a, b);
    int delta = Sqr[a * a - b * b];
    if (delta == -1) return false;
    return __gcd(b, delta) == 1;
}

int main() {
    int a, b;
    memset(Sqr, -1, sizeof(Sqr));
    for (int i = 1; i <= 1000; i++) Sqr[i * i] = i;

    while (~scanf("%d%d", &a, &b)) {
        init();
        int n = b - a + 1;
        int s = 0, t = 2 * n + 1;
        for (int i = a; i <= b; i++) {
            addedge(s, i - a + 1, i, 1);
            addedge(i - a + 1 + n, t, i, 1);
            for (int j = a; j <= b; j++) {
                if (check(i, j)) {
                    addedge(i - a + 1, j - a + 1 + n, 0, 1);
                }
            }
        }
        pii ret = mcmf(s, t);
        printf("%d %d\n", ret.fi / 2, ret.se / 2);
    }
    return 0;
}
