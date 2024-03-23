#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 111;
int eh[N], tot;
int dist[N], low[N];
int anscost, ans;
int pre[N];
bool visit[N];
int n, m, a[N][N];

struct Edge {
    int u, v, cost, cap, flow, next;
    Edge(int u, int v, int cost, int cap, int flow, int next) : u(u), v(v), cost(cost), cap(cap), flow(flow), next(next) {}
    Edge() {}
} et[N * N];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cost, int cap, int flow) {
    et[tot] = Edge(u, v, cost, cap, flow, eh[u]);
    eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap) {
    add(u, v, cost, cap, 0);
    add(v, u, -cost, 0, 0);
}

bool spfa(int s, int t) {
    queue<int> que;
    for (int i = 0; i < N; i++) dist[i] = INT_MAX;
    low[s] = INT_MAX;
    pre[s] = -1;
    dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            if (et[i].cap > et[i].flow && dist[v] > dist[u] + et[i].cost) {
                dist[v] = dist[u] + et[i].cost;
                low[v] = min(low[u], et[i].cap - et[i].flow);
                pre[v] = i;
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dist[t] != INT_MAX;
}

void aug(int s, int t) {
    ans += low[t];
    anscost += low[t] * dist[t];
    int x = pre[t];
    while (x != -1) {
        et[x].flow += low[t];
        et[x ^ 1].flow -= low[t];
        x = pre[et[x].u];
    }
}

void mcmf(int s, int t) {
    ans = anscost = 0;
    while (spfa(s, t)) aug(s, t);
}

int calc(int a[], int n, int target) {
    init();
    int s = n, t = n + 1;
    for (int i = 0; i < n; i++) {
        addedge(s, i, 0, a[i]);
        addedge(i, t, 0, target);
        if (i - 1 >= 0) addedge(i, i - 1, 1, INT_MAX);
        if (i + 1 < n) addedge(i, i + 1, 1, INT_MAX);
    }
    mcmf(s, t);
    return anscost;
}

int X, Y;
int row[N], col[N];
void solve() {
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            row[i] += a[i][j];
            col[j] += a[i][j];
            sum += a[i][j];
        }
    }
    int minRP = INT_MAX;
    for (int used = 0; used <= sum; used++) {
        if ((used % n) || (used % m)) continue;
        minRP = min(minRP, (calc(row, n, used / n) + calc(col, m, used / m)) * X + (sum - used) * Y);
    }
    printf("%d\n", minRP);
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        scanf("%d%d", &X, &Y);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        solve();
    }
    return 0;
}
