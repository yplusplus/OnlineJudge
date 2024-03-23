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
#define maxn 250
#define maxm 505050
int ans, anscost, eh[maxn], tot, low[maxn], p[maxn], dist[maxn]; 
int S, T;
int n, m, k;
int maz[maxn][maxn];
struct Edge {
    int u, v, cost, cap, flow, next; 
} et[maxm];
bool visit[maxn];
bool spfa() {
    queue<int> que;
    memset(visit, false, sizeof (visit));
    memset(p, -1, sizeof (p));
    memset(low, 0, sizeof(low));
    fill(&dist[0], &dist[maxn], inf);
    visit[S] = true, low[S] = inf, dist[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
            if (flow < cap && dist[u] + cost < dist[v]) {
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
    return dist[T] != inf;
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

void floyd() {
    for(int k = 0; k <= n; k++)
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= n; j++)
                maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
}

int main() {
    while(~scanf("%d%d%d", &n, &m, &k)) {
        if(!n && !m && !k) break;
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= n; j++)
                maz[i][j] = i == j ? 0 : inf;
        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if(c < maz[a][b]) maz[a][b] = c;
            maz[b][a] = maz[a][b];
        }
        floyd();
        init();
        S = 0, T = 2 * n + 2;
        addedge(S, T - 1, 0, k);
        for(int i = 1; i <= n; i++) {
            addedge(S, i, -maz[i][0], 1);
            addedge(T - 1, i + n, maz[i][0], 1);
            addedge(i + n, T, maz[i][0], 1);
            for(int j = i + 1; j <= n; j++) {
                addedge(i, j + n, maz[i][j], 1);
            }
        }
        costflow();
        cout << anscost << endl;
    }
    return 0;
}
