#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 111111;
vector<int> vec[N];
int val[N];
int st[N], ed[N], fa[N];
int tot;
int n, k;
vector<pair<int, LL> > leafs;

struct Node {
    LL maxm, minus;
    int id;
};

struct SegTree {
    Node node[N << 2];
    void build(int p, int l, int r) {
        node[p].minus = 0;
        if (l == r) {
            node[p].maxm = leafs[l - 1].second;
            node[p].id = leafs[l - 1].first;
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        push_up(p, l, r);
    }
    void minus(int p, int l, int r, int L, int R, LL x) {
        if (L <= l && r <= R) {
            node[p].minus += x;
            node[p].maxm -= x;
            return;
        }
        push_down(p, l, r);
        int mid = l + r >> 1;
        if (L <= mid) minus(p << 1, l, mid, L, R, x);
        if (mid < R) minus(p << 1 | 1, mid + 1, r, L, R, x);
        push_up(p, l, r);
    }
    void push_up(int p, int l, int r) {
        if (node[p << 1].maxm > node[p << 1 | 1].maxm) {
            node[p].maxm = node[p << 1].maxm;
            node[p].id = node[p << 1].id;
        } else {
            node[p].maxm = node[p << 1 | 1].maxm;
            node[p].id = node[p << 1 | 1].id;
        }
    }
    void push_down(int p, int l, int r) {
        if (node[p].minus > 0) {
            node[p << 1].maxm -= node[p].minus;
            node[p << 1 | 1].maxm -= node[p].minus;
            node[p << 1].minus += node[p].minus;
            node[p << 1 | 1].minus += node[p].minus;
            node[p].minus = 0;
        }
    }
} seg_tree;

void dfs(int u, LL sum) {
    sum += val[u];
    st[u] = tot + 1;
    if (vec[u].size() > 0) {
        for (int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i];
            dfs(v, sum);
        }
    } else {
        leafs.push_back(pair<int, LL>(u, sum));
        tot++;
    }
    ed[u] = tot;
}

void solve() {
    leafs.clear();
    tot = 0;
    dfs(1, 0LL);
    /*
    for (int i = 0; i < leafs.size(); i++) {
        cout << leafs[i].first << " " << leafs[i].second << endl;
    }
    */
    seg_tree.build(1, 1, leafs.size());
    LL ans = 0;
    bool del[N] = {0};
    for (int i = 0; i < k; i++) {
        if (seg_tree.node[1].maxm == 0) break;
        //cout << i << " " << seg_tree.node[1].maxm << endl;
        ans += seg_tree.node[1].maxm;
        int u = seg_tree.node[1].id;
        while (u != -1 && !del[u]) {
            //cout << u << " " << st[u] << " " << ed[u] << " " << val[u] << endl;
            seg_tree.minus(1, 1, leafs.size(), st[u], ed[u], val[u]);
            del[u] = true;
            u = fa[u];
        }
        //cout << i << " " << seg_tree.node[1].maxm << endl;
    }
    cout << ans << endl;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            fa[b] = a;
            vec[a].push_back(b);
        }
        fa[1] = -1;
        printf("Case #%d: ", Case++);
        solve();
    }
    return 0;
}
