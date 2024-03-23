#include <iostream>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <climits>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;

const int N = 666;
const int M = N * N;
int eh[N], tot;
int n, m, k;
int dist[N], cur[N];
int deg[N];
struct Edge {
    int u, v, cap, flow, next;
    Edge() {}
    Edge(int u, int v, int cap, int flow, int next) : u(u), v(v), cap(cap), flow(flow), next(next) {}
} et[M];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
    et[tot] = Edge(u, v, cap, flow, eh[u]);
    eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
    add(u, v, cap, 0);
    add(v, u, 0, 0);
}

bool bfs(int s, int t) {
    queue<int> que;
    memset(dist, -1, sizeof(dist));
    que.push(s);
    dist[s] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            if (et[i].cap > et[i].flow && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
    return dist[t] != -1;
}

int dfs(int u, int t, int d) {
    if (u == t) return d;
    int l = d;
    for (int &i = cur[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (et[i].cap > et[i].flow && dist[v] == dist[u] + 1) {
            int tmp = dfs(v, t, min(et[i].cap - et[i].flow, l));
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
        res += dfs(s, t, INT_MAX);
    }
    return res;
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &k)) {
        init();
        for (int i = 1; i <= n + m; i++) deg[i] = -2;
        for (int i = 0; i < k; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            v += n;
            addedge(u, v, 1);
            deg[u]++;
            deg[v]++;
        }
        int s = 0, t = n + m + 1;
        if (*min_element(deg + 1, deg + 1 + n + m) < 0) {
            puts("-1");
            continue;
        }
        //for (int i = 1; i <= n + m; i++) { cout << i << " " << deg[i] << endl; }
        for (int i = 1; i <= n; i++) {
            addedge(s, i, deg[i]);
        }
        for (int i = 1; i <= m; i++) {
            addedge(n + i, t, deg[n + i]);
        }
        int ans = k - Dinic(s, t);
        vector<int> edgeId;
        for (int i = 0; i < 2 * k; i += 2) {
            if (et[i].flow < et[i].cap) {
                edgeId.push_back((i >> 1) + 1);
            }
        }
        assert(ans == edgeId.size());
        //cout << ans << endl;
        printf("%d\n", edgeId.size());
        for (int i = 0; i < edgeId.size(); i++) {
            printf("%d%c", edgeId[i], i == edgeId.size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

