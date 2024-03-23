#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define lson(x) ((x) << 1)
#define rson(x) (lson(x) | 1)

const int N = 111111;
int val[N];
vector<int> vec[N];
int son[N], heavy[N], belong[N];
int st[N], ed[N], tot;
int que[N], dep[N], f[N];
int n;

void dfs(int u, int fa) {
    heavy[u] = son[u] = 0;
    f[u] = fa;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa) continue;
        dfs(v, u);
        son[u] += son[v];
        if (heavy[u] == 0 || son[v] > son[heavy[u]]) heavy[u] = v;
    }
}

void dfs2(int u, int cc, int depth) {
    que[++tot] = u;
    st[u] = tot;
    belong[u] = cc;
    dep[u] = depth;
    if (heavy[u]) dfs2(heavy[u], cc, depth + 1);
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == f[u] || v == heavy[u]) continue;
        dfs2(v, v, depth + 1);
    }
    ed[u] = tot;
}

struct SegTree {
    int sum[N << 2];
    int csum[N << 2];
    int cover[N << 2];
    void pushup(int p, int l, int r) {
        sum[p] = sum[lson(p)] + sum[rson(p)];
        csum[p] = csum[lson(p)] + csum[rson(p)];
    }
    void pushdonwn(int p, int l, int r) {
        if (cover[p]) {
            csum[lson(p)] = sum[lson(p)];
            csum[rson(p)] = sum[rson(p)];
            cover[lson(p)] = cover[rson(p)] = 1;
            cover[p] = 0;
        }
    }
    void build(int p, int l, int r) {
        cover[p] = 0;
        if (l == r) {
            sum[p] = val[que[l]];
            csum[p] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(lson(p), l, mid);
        build(rson(p), mid + 1, r);
        pushup(p, l, r);
    }
    void modify(int p, int l, int r, int L, int R, int c) {
        if (L <= l && r <= R) {
            cover[p] = c;
            csum[p] = c ? sum[p] : 0;
            return;
        }
        pushdonwn(p, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) modify(lson(p), l, mid, L, R, c);
        if (mid < R) modify(rson(p), mid + 1, r, L, R, c);
        pushup(p, l, r);
    }
} seg_tree;

void solve() {
    tot = 0;
    son[0] = 0;
    dfs(1, 0);
    dfs2(1, 1, 1);
    seg_tree.build(1, 1, n);
    int Q, cmd, a, b;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d%d", &cmd, &a);
        if (cmd == 1) {
            scanf("%d", &b);
            while (belong[a] != belong[b]) {
                if (dep[belong[a]] < dep[belong[b]]) swap(a, b);
                seg_tree.modify(1, 1, n, st[belong[a]], st[a], 1);
                a = f[belong[a]];
            }
            if (dep[a] > dep[b]) swap(a, b);
            seg_tree.modify(1, 1, n, st[a], st[b], 1);
        } else if (cmd == 2) {
            seg_tree.modify(1, 1, n, st[a], st[a], 0);
        } else {
            seg_tree.modify(1, 1, n, st[a], ed[a], 1);
        }
        printf("%d\n", seg_tree.csum[1]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            vec[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].push_back(b);
            vec[b].push_back(a);
        }
        solve();
    }
    return 0;
}
