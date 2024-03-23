#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 111111;

vector<pair<int, int> > vec[N];
int fa[N];
int son[N], dep[N], val[N], pos[N];
int belong[N];
int tot, n, q, s;
int heavy[N];
pair<int, int> edge[N];

struct BIT {
    int c[N];
    int lowbit(int x) { return x & (-x); }
    void clear() { memset(c, 0, sizeof(c)); }
    int query(int x) { int res = 0; for (; x > 0; x -= lowbit(x)) res += c[x]; return res; }
    void add(int x, int v) { for (; x <= n; x += lowbit(x)) c[x] += v; }
    int query(int l, int r) { int res = 0; if (r) res += query(r); if (l > 1) res -= query(l - 1); return res; }
} bit;

void dfs(int u, int depth) {
    son[u] = 1;
    dep[u] = depth;
    heavy[u] = 0;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (v == fa[u]) continue;
        fa[v] = u;
        dfs(v, depth + 1);
        if (heavy[u] == 0 || son[heavy[u]] < son[v]) { heavy[u] = v; }
        val[v] = vec[u][i].second;
        son[u] += son[v];
    }
}

void dfs2(int u, int cc) {
    pos[u] = ++tot;
    bit.add(tot, val[u]);
    belong[u] = cc;
    if (!heavy[u]) return;
    dfs2(heavy[u], cc);
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (v == fa[u]) continue;
        if (v != heavy[u])
            dfs2(v, v);
    }
}

int query(int a, int b) {
    int res = 0;
    while (belong[a] != belong[b]) {
        if (dep[belong[a]] < dep[belong[b]]) {
            swap(a, b);
        }
        res += bit.query(pos[belong[a]], pos[a]);
        a = fa[belong[a]];
    }
    if (dep[a] > dep[b]) swap(a, b);
    if (pos[a] + 1 <= pos[b])
        res += bit.query(pos[a] + 1, pos[b]);
    return res;
}

void solve() {
    tot = 0;
    fa[1] = 0;
    bit.clear();
    dfs(1, 1);
    dfs2(1, 1);
    int cmd, x, y;
    for (int i = 0; i < q; i++) {
        scanf("%d%d", &cmd, &x);
        if (cmd == 0) {
            // query
            int res = query(s, x);
            s = x;
            printf("%d\n", res);
        } else {
            // modify
            scanf("%d", &y);
            int a = edge[x].first, b = edge[x].second;
            if (fa[a] != b) swap(a, b);
            bit.add(pos[a], y - val[a]);
            val[a] = y;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &q, &s);
    for (int i = 1; i <= n; i++) { vec[i].clear(); }
    for (int i = 1; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        vec[a].push_back(make_pair(b, c));
        vec[b].push_back(make_pair(a, c));
        edge[i].first = a;
        edge[i].second = b;
    }
    solve();
    return 0;
}
