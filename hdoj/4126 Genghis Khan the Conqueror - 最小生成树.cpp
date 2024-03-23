#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 3333;
const int INF = 100000000;
bool tree_edge[N][N];
int weight[N][N], mi[N][N];
int dist[N];
int n, m;
vector<int> tree[N];

int prim() {
    int ans = 0;
    static int pre[N];
    static bool visit[N];
    memset(tree_edge, 0, sizeof(tree_edge));
    memset(visit, 0, sizeof(visit));
    memset(pre, -1, sizeof(pre));
    for (int i = 0; i < n; i++) tree[i].clear();
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[0] = 0;
    while (true) {
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!visit[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        if (u == -1) break;
        visit[u] = true;
        ans += dist[u];
        if (pre[u] != -1) {
            tree_edge[pre[u]][u] = tree_edge[u][pre[u]] = true;
            tree[u].push_back(pre[u]);
            tree[pre[u]].push_back(u);
        }
        for (int v = 0; v < n; v++) {
            if (!visit[v] && dist[v] > weight[u][v]) {
                dist[v] = weight[u][v];
                pre[v] = u;
            }
        }
    }
    return ans;
}

int dfs(int u, int fa, int root) {
    int res = INF;
    if (root != fa && root != u) res = weight[u][root];
    for (int i = 0; i < tree[u].size(); i++) {
        int v = tree[u][i];
        if (v == fa) continue;
        res = min(res, dfs(v, u, root));
    }
    if (fa != -1) {
        mi[u][fa] = min(mi[u][fa], res);
        mi[fa][u] = mi[u][fa];
    }
    return res;
}

void solve() {
    int mst = prim();
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) mi[i][j] = INF;
    for (int u = 0; u < n; u++) { dfs(u, -1, u); }
    int q;
    scanf("%d", &q);
    double ans = 0;
    for (int i = 0, a, b, c; i < q; i++) {
        scanf("%d%d%d", &a, &b, &c);
        if (!tree_edge[a][b]) ans += mst;
        else ans += mst - weight[a][b] + min(c, mi[a][b]);
    }
    ans /= q;
    printf("%.4f\n", ans);
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        if (!n && !m) break;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) weight[i][j] = INF;
        for (int i = 0, a, b, c; i < m; i++) {
            scanf("%d%d%d", &a, &b, &c);
            weight[a][b] = min(weight[a][b], c);
            weight[b][a] = weight[a][b];
        }
        solve();
    }
    return 0;
}
