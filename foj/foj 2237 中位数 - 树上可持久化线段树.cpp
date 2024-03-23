#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

const int N = 55555;
const int M = 1000010;
const int LIMIT = 100000;
int n, m;
int fa[N], dep[N], pos[N], tot, f[2 * N];
int rmq[2 * N][18];
vector<pair<int, int> > vec[N];
int root[N];
int nodecnt;

struct Node {
    int l, r, cnt;
} node[M];

void push_up(int p) { node[p].cnt = node[node[p].l].cnt + node[node[p].r].cnt; }

int insert(int p, int l, int r, int v) {
    int k = ++nodecnt;
    if (l == r) {
        node[k].l = node[k].r = 0;
        node[k].cnt = node[p].cnt + 1;
        return k;
    }
    int mid = (l + r) >> 1;
    if (v <= mid) {
        node[k].l = insert(node[p].l, l, mid, v);
        node[k].r = node[p].r;
    } else {
        node[k].l = node[p].l;
        node[k].r = insert(node[p].r, mid + 1, r, v);
    }
    push_up(k);
    return k;
}

void dfs(int u, int father, int d) {
    tot++;
    fa[u] = father;
    pos[u] = tot;
    dep[u] = d;
    f[tot] = u;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (v == father) continue;
        root[v] = insert(root[u], 0, LIMIT, vec[u][i].second);
        dfs(v, u, d + 1);
        f[++tot] = u;
    }
}

void init_rmq() {
    for (int i = 1; i <= tot; i++) {
        rmq[i][0] = f[i];
    }
    for (int j = 1; (1 << j) <= tot; j++) {
        for (int i = 1; i + (1 << j) - 1 <= tot; i++) {
            int a = rmq[i][j - 1];
            int b = rmq[i + (1 << j - 1)][j - 1];
            rmq[i][j] = dep[a] < dep[b] ? a : b;
        }
    }
}

int lca(int u, int v) {
    int upos = pos[u];
    int vpos = pos[v];
    if (upos > vpos) swap(upos, vpos);
    int k = log(vpos - upos + 1) / log(2.0);
    int a = rmq[upos][k];
    int b = rmq[vpos - (1 << k) + 1][k];
    return dep[a] < dep[b] ? a : b;
}

int query(int u, int v, int w, int l, int r, int k) {
    if (l == r) return l;
    int res = node[node[u].l].cnt + node[node[v].l].cnt - 2 * node[node[w].l].cnt;
    int mid = (l + r) / 2;
    if (res >= k) {
        return query(node[u].l, node[v].l, node[w].l, l, mid, k);
    } else {
        return query(node[u].r, node[v].r, node[w].r, mid + 1, r, k - res);
    }
}

void solve() {
    for (int i = 1; i <= n; i++) vec[i].clear();
    tot = nodecnt = 0;
    memset(&node[0], 0, sizeof(node[0]));

    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        vec[u].push_back(make_pair(v, w));
        vec[v].push_back(make_pair(u, w));
    }

    root[1] = 0;
    dfs(1, 0, 1);
    init_rmq();

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        int _lca = lca(u, v);
        int k = (dep[u] + dep[v] - 2 * dep[_lca] + 1) / 2;
        printf("%d\n", query(root[u], root[v], root[_lca], 0, LIMIT, k));
    }
}

int main() {

    while (~scanf("%d%d", &n, &m)) {
        solve();
    }

    return 0;
}