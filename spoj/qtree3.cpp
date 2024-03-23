#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;

const int N = 100010;
vector<int> vec[N];
int color[N];
int fa[N], dfn[N], tot;
int top[N], heavy[N];
int son[N];
int n;

struct SegTree {
    int black[N << 2];
    void clear() { memset(black, 0, sizeof(black)); }
    void modify(int p, int l, int r, int x, int v) {
        if (l == r) {
            black[p] = v;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) modify(p << 1, l, mid, x, v);
        else modify(p << 1 | 1, mid + 1, r, x, v);
        if (black[p << 1]) {
            black[p] = black[p << 1];
        } else {
            black[p] = black[p << 1 | 1];
        }
    }
    int query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) return black[p];
        int mid = (l + r) / 2;
        int res = 0;
        if (L <= mid) { res = query(p << 1, l, mid, L, R); }
        if (mid < R && res == 0) { res = query(p << 1 | 1, mid + 1, r, L, R); }
        return res;
    }
} seg_tree;

void dfs(int u, int f) {
    fa[u] = f;
    heavy[u] = 0;
    son[u] = 1;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa[u]) continue;
        dfs(v, u);
        son[u] += son[v];
        if (heavy[u] == 0 || son[v] > son[heavy[u]]) heavy[u] = v;
    }
}

void dfs_heavy(int u, int c) {
    dfn[u] = ++tot;
    top[u] = c;
    if (heavy[u] == 0) return;
    dfs_heavy(heavy[u], c);
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa[u] || v == heavy[u]) continue;
        dfs_heavy(v, v);
    }
}

int query(int x) {
    int res = 0;
    while (x) {
        int ret = seg_tree.query(1, 1, n, dfn[top[x]], dfn[x]);
        if (ret != 0) res = ret;
        x = fa[top[x]];
    }
    return res;
}

int main() {
    int q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        vec[i].clear();
        color[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    tot = 0;
    dfs(1, 0);
    dfs_heavy(1, 1);

    int x, y;
    for (int i = 0; i < q; i++) {
        scanf("%d%d", &x, &y);
        if (x == 0) {
            seg_tree.modify(1, 1, n, dfn[y], color[y] == 0 ? y : 0);
            color[y] ^= 1;
        } else {
            int ans = query(y);
            if (ans == 0) ans = -1;
            printf("%d\n", ans);
        }
    }

    return 0;
}
