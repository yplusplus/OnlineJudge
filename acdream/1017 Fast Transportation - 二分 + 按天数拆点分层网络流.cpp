#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 111;
const int NN = 8888;
const int M = 1888888;
const int inf = 1 << 30;
int g[N][N];
int eh[NN], tot;
int dist[NN], cur[NN];
int n, m, cars, st, ed;

struct Edge {
    int v, cap, flow, next;
} et[M];

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

bool bfs(int s, int t) {
    queue<int> que;
    memset(dist, -1, sizeof(dist));
    dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front(); que.pop();
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

int dfs(int u, int d, int t) {
    if (u == t) return d;
    int l = d;
    for (int &i = cur[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (et[i].cap > et[i].flow && dist[u] + 1 == dist[v]) {
            int tmp = dfs(v, min(et[i].cap - et[i].flow, l), t);
            et[i].flow += tmp;
            et[i ^ 1].flow -= tmp;
            l -= tmp;
            if (l == 0) break;
        }
    }
    return d - l;
}

int Dinic(int s, int t) {
    int res = 0;
    while (bfs(s, t)) {
        memcpy(cur, eh, sizeof(eh));
        res += dfs(s, inf, t);
    }
    return res;
}

bool check(int days) {
    init();
    int s = 0, t = n * (days + 1) + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < days; j++) {
            addedge(i + j * n, i + (j + 1) * n, inf);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && g[i][j]) {
                for (int k = 0; k < days; k++) {
                    addedge(i + k * n, j + (k + 1) * n, 1); 
                }
            }
        }
    }
    addedge(s, st, cars);
    addedge(ed + n * days, t, cars);
    int ret = Dinic(s, t);
    return ret == cars;
}

void solve() {
    int l = 0, r = n + cars;
    int ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d%d%d%d%d", &n, &m, &cars, &st, &ed)) {
        memset(g, 0, sizeof(g));
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            g[a][b] = g[b][a] = 1;
        }
        solve();
    }
    return 0;
}
