#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 30
#define maxm 50000
const int inf = 1 << 29;
int ans, anscost, eh[maxn], tot, low[maxn], p[maxn], dist[maxn];
int s, t, n, m, k;
int b[maxn], a[maxn][maxn];
struct Edge {
    int u, v, cost, cap, flow, next;
} et[maxm];
bool visit[maxn];

void init() {
    tot = 0;
    memset(eh, -1, sizeof (eh));
}

void add(int u, int v, int cost, int cap, int flow) {
    Edge e = {u, v, cost, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap) {
    add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}

bool spfa() {
    queue<int> que;
    memset(visit, false, sizeof (visit));
    memset(p, -1, sizeof (p));
    memset(low, 0, sizeof(low));
    fill(&dist[0], &dist[maxn], -inf);
    visit[s] = true, low[s] = inf, dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
            if (flow < cap && dist[u] + cost > dist[v]) {
                dist[v] = dist[u] + cost;
                p[v] = i;
                low[v] = min(low[u], cap - flow);
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dist[t] != -inf;
}

void costflow() {
    ans = 0, anscost = 0;
    while (spfa()) {
        int x = p[t];
        ans += low[t];
        anscost += low[t] * dist[t];
        while (x != -1) {
            et[x].flow += low[t];
            et[x^1].flow -= low[t];
            et[x^1].cost = -et[x].cost;
            x = p[et[x].u];
        }
    }
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &k);
        int sum = 0;
        for(int i = 1; i <= m; i++) {
            scanf("%d", &b[i]);
            sum += b[i];
        }
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        s = 0, t = n + m + 1;
        init();
        for(int i = 1; i <= n; i++) {
            addedge(s, i, 0, 1);
            for(int j = 1; j <= m; j++) {
                if(a[j][i]) addedge(i, n + j, 0, 1);
            }
        }
        for(int i = 1; i <= m; i++) {
            addedge(n + i, t, k, b[i] / k);
            if(b[i] % k > 1) addedge(n + i, t, b[i] % k, 1);
        }
        costflow();
        printf("Case #%d: ", Case++);
        if(n - ans + anscost >= sum) puts("YES");
        else puts("NO");
    }
    return 0;
}

