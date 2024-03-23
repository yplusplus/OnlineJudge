#include <iostream>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

#define mp make_pair
typedef long long LL;
typedef pair<int, int> PII;
const int N = 250025;
const int M = 19;
int n, m;
vector<PII> tree[N];
vector<int> vtree[N];
int res[N];
int dfn[N], dfncc;
int fa[N][M];
int minv[N][M];
int dep[N];
bool is_res[N];

bool cmp_by_dfn(int a, int b) { return dfn[a] < dfn[b]; }

void vaddedge(int u, int v) { vtree[u].push_back(v); }

void tree_dfs(int u) {
    dfncc++;
    dfn[u] = dfncc;
    dep[u] = dep[fa[u][0]] + 1;
    if (fa[u][0]) {
        for (int i = 1; i < M; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
            if (fa[u][i] == 0) break;
            minv[u][i] = min(minv[u][i - 1], minv[fa[u][i - 1]][i - 1]);
        }
    }
    for (int i = 0; i < tree[u].size(); i++) {
        int v = tree[u][i].first;
        if (v == fa[u][0]) continue;
        fa[v][0] = u;
        minv[v][0] = tree[u][i].second;
        tree_dfs(v);
    }
}

int lca(int a, int b) {
    if (a == 0 || b == 0) return 0;
    if (dep[a] < dep[b]) swap(a, b);
    int d = dep[a] - dep[b];
    for (int i = 0; i < M; i++) {
        if (d & (1 << i)) {
            a = fa[a][i];
        }
    }
    if (a == b) return a;
    for (int i = M - 1; i >= 0; i--) {
        if (fa[a][i] != fa[b][i]) {
            a = fa[a][i]; b = fa[b][i];
        }
    }
    assert(fa[a][0] == fa[b][0]);
    return fa[a][0];
}

int get_minv(int u, int k) {
    int res = INT_MAX;
    for (int i = 0; i < M; i++) {
        if (k & (1 << i)) {
            res = min(res, minv[u][i]);
            u = fa[u][i];
        }
    }
    return res;
}

LL dfs(int u) {
    if (is_res[u]) return LLONG_MAX;
    LL res = 0;
    for (int i = 0; i < vtree[u].size(); i++) {
        int v = vtree[u][i];
        res += min((LL)get_minv(v, dep[v] - dep[u]), dfs(v));
    }
    return res;
}

void solve() {
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &res[i]);
        is_res[res[i]] = true;
    }
    sort(res, res + m, cmp_by_dfn);
    static int st[N];
    int top = 0;
    st[++top] = 1;
    for (int i = 0, mm = m; i < mm; i++) {
        int lca_ = lca(res[i], st[top]);
        while (top && dfn[lca_] < dfn[st[top]]) {
            int popv = st[top--];
            if (top && dfn[lca_] < dfn[st[top]]) {
                vaddedge(st[top], popv);
            } else {
                vaddedge(lca_, popv);
                break;
            }
        }
        if (dfn[st[top]] != dfn[lca_]) {
            st[++top] = lca_;
            res[m++] = lca_;
        }
        st[++top] = res[i];
    }
    res[m++] = 1;
    
    while (top) {
        if (top > 1) vaddedge(st[top - 1], st[top]);
        top--;
    }
    LL ans = dfs(1);
    printf("%lld\n", ans);
    
    // clear
    for (int i = 0; i < m; i++) {
        vtree[res[i]].clear();
        is_res[res[i]] = false;
    }
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) tree[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            tree[u].push_back(mp(v, w));
            tree[v].push_back(mp(u, w));
        }
        
        memset(fa, 0, sizeof(fa));
        dep[0] = 0;
        dfncc = 0;
        tree_dfs(1);
        
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            solve();
        }
    }
    
    return 0;
}
