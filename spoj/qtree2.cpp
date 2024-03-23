#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

#define mp make_pair
typedef pair<int, int> PII;
const int M = 18;
const int N = 11111;
vector<PII> vec[N];
int fa[N][M], dep[N];
int path[N], n;

void dfs(int u, int f, int w) {
    path[u] = w;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (v == f) continue;

        fa[v][0] = u;
        for (int j = 1; j < M; j++) {
            if (fa[v][j - 1] == 0) break;
            fa[v][j] = fa[fa[v][j - 1]][j - 1];
        }
        dep[v] = dep[u] + 1;
        dfs(v, u, w + vec[u][i].second);
    }
}

int kth_anc(int a, int k) {
    for (int i = 0; i < M; i++) {
        if (k & (1 << i)) a = fa[a][i];
    }
    return a;
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    if (dep[a] != dep[b]) a = kth_anc(a, dep[a] - dep[b]);
    if (a == b) return a;
    for (int i = M - 1; i >= 0; i--) {
        if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    }
    return fa[a][0];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            vec[i].clear();
            for (int j = 0; j < M; j++) fa[i][j] = 0;
        }

        int a, b, c;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &a, &b, &c);
            vec[a].push_back(mp(b, c));
            vec[b].push_back(mp(a, c));
        }

        dep[1] = 0;
        dfs(1, 0, 0);

        char cmd[20];
        while (scanf("%s", cmd) && cmd[1] != 'O') {
            scanf("%d%d", &a, &b);
            int _lca = lca(a, b);
            if (cmd[0] == 'D') {
                printf("%d\n", path[a] + path[b] - 2 * path[_lca]);
            } else {
                scanf("%d", &c);
                int _lca = lca(a, b);
                int alen = dep[a] + 1 - dep[_lca];
                int blen = dep[b] + 1 - dep[_lca];
                int ans = 0;
                if (c <= alen) {
                    ans = kth_anc(a, c - 1);
                } else {
                    ans = kth_anc(b, alen + blen - c - 1);
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
