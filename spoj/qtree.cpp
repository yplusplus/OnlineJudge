#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

#define mp make_pair
typedef pair<int, int> PII;
const int N = 11111;
vector<PII> vec[N];
int top[N], cnt[N], tot;
int heavy[N], fa[N], dep[N], dfn[N];
int enode[N], evalue[N];
int n;

struct SegTree {
    int mx[N << 2];
    void clear() { memset(mx, 0, sizeof(mx)); }
    void modify(int p, int l, int r, int x, int v) {
        if (l == r) { mx[p] = v; return; }
        int mid = (l + r) >> 1;
        if (x <= mid) modify(p << 1, l, mid, x, v);
        else modify(p << 1 | 1, mid + 1, r, x, v);
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }
    int query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) { return mx[p]; }
        int mid = (l + r) >> 1;
        int res = 0;
        if (L <= mid) res = max(res, query(p << 1, l, mid, L, R));
        if (mid < R) res = max(res, query(p << 1 | 1, mid + 1, r, L, R));
        return res;
    }
} seg_tree;

void dfs(int u, int f) {
    cnt[u] = 1;
    heavy[u] = 0;
    fa[u] = f;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (v == f) continue;
        enode[vec[u][i].second] = v;
        dep[v] = dep[u] + 1;
        dfs(v, u);
        cnt[u] += cnt[v];
        if (heavy[u] == 0 || cnt[heavy[u]] < cnt[v]) heavy[u] = v;
    }
}

void dfs2(int u, int c) {
    top[u] = c;
    dfn[u] = ++tot;
    if (!heavy[u]) return;
    dfs2(heavy[u], c);
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (v != fa[u] && v != heavy[u]) 
            dfs2(v, v);
    }
}

int query(int a, int b) {
    int res = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        res = max(res, seg_tree.query(1, 1, n, dfn[top[a]], dfn[a]));
        a = fa[top[a]];
    }
    if (dep[a] > dep[b]) swap(a, b);
    if (a != b) res = max(res, seg_tree.query(1, 1, n, dfn[a] + 1, dfn[b]));
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n); 
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &evalue[i]);
            vec[a].push_back(mp(b, i));
            vec[b].push_back(mp(a, i));
        }

        tot = 0;
        dep[1] = 0;
        dfs(1, 0);
        dfs2(1, 1);
        seg_tree.clear();
        for (int i = 1; i < n; i++) {
            seg_tree.modify(1, 1, n, dfn[enode[i]], evalue[i]);
        }

        char cmd[20];
        int a, b;
        while (scanf("%s", cmd) && cmd[0] != 'D') {
            if (cmd[0] == 'C') {
                scanf("%d%d", &a, &b);
                seg_tree.modify(1, 1, n, dfn[enode[a]], b);
            } else {
                scanf("%d%d", &a, &b);
                int ret = query(a, b);
                printf("%d\n", ret);
            }
        }
    }
    return 0;
}
