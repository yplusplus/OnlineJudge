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
const int inf = 1 << 25;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define eps 1e-8
#define maxn 100
int w[maxn];
int x[maxn], y[maxn];
int hasClass[50][50];
int n, m, k;
int ans, anscost, eh[maxn], tot, low[maxn], p[maxn], dist[maxn]; 
int S, T;
bool visit[maxn];
struct Edge {
    int u, v, cost, cap, flow, next; 
}et[500000];
bool spfa() {
    queue<int> que;
    memset(visit, false, sizeof (visit));
    memset(p, -1, sizeof (p));
    memset(low, 0, sizeof(low));
    for(int i = 0; i < maxn; i++) dist[i] = -inf;
    visit[S] = true, low[S] = inf, dist[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
            if (flow < cap && dist[u] + cost > dist[v]) {
                dist[v] = dist[u] + cost;
                p[v] = i; //注意，这里是 i
                low[v] = min(low[u], cap - flow);
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dist[T] != -inf;
}
void costflow() {
    ans = 0, anscost = 0;
    while (spfa()) {
        int x = p[T];
        ans += low[T];
        anscost += low[T] * dist[T];
        while (x != -1) {
            et[x].flow += low[T];
            et[x^1].flow -= low[T];
            et[x^1].cost = -et[x].cost;
            x = p[et[x].u];
        }
    }
}
void add(int u, int v, int cost, int cap, int flow) {
    Edge e = {u, v, cost, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}
void addedge(int u, int v, int cost, int cap) {
    add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}
void init() {
    tot = 0;
    memset(eh, -1, sizeof (eh));
}

int main() {
    while(~scanf("%d%d%d", &n, &k, &m)) {
        if(!n && !m && !k) break;
        S = 0, T = n + m + 1;
        double sum = 0.0;
        for(int i = 1; i <= m; i++) {
            scanf("%d", &w[i]);
            sum += 1.0 * w[i];
        }
        for(int i = 1; i <= m; i++) {
            scanf("%d", &x[i]);
        }
        memset(hasClass, 0, sizeof(hasClass));
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                scanf("%d", &hasClass[i][j]);
        init();
        for(int i = 1; i <= n; i++) {
            addedge(S, i, 0, k);
            for(int j = 1; j <= m; j++) {
                if(hasClass[i][j]) {
                    addedge(i, j + n, 0, inf);
                }
            }
        }
        for(int i = 1; i <= m; i++) {
            if(x[i] < 60) {
                addedge(i + n, T, inf, 60 - x[i]);
            }
            for(int j = max(60, x[i]); j < 100; j++) {
                addedge(i + n, T, (199 - 2 * j) * w[i], 1);
            }
        }
        costflow();
        memset(y, 0, sizeof(y));
        bool found = false;
        for(int i = 1; i <= m; i++) {
            for(int j = eh[i + n]; j != -1; j = et[j].next) {
                if(et[j].v != T) continue;
                int flow = et[j].flow;
                y[i] += flow;
            }
            if(x[i] + y[i] < 60) found = true;
        }
        if(found) puts("0.000000");
        else {
            double ans = 0.0;
            for(int i = 1; i <= m; i++) {
                double tmp = (4.0 - 3 * (100.0 - x[i] - y[i]) * (100.0 - x[i] - y[i]) / 1600.0);
                ans += tmp * 1.0 * w[i];
            }
            ans /= sum;
            printf("%.6f\n", ans + eps);
        }
    }
    return 0;
}
