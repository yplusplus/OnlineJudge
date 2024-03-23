#pragma comment(linker, "/STACK:10006777216")
#include <cassert>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 100010;
const int M = 18;
int eh[N], tot;
int rmq[N << 1][M], rn;
int F[N << 1], B[N << 1], pos[N];
int father[N][M];
int st[N], ed[N], dep[N];
int n;
int lg[N << 1];

struct Edge {
    int u, v, next;
    Edge() {}
    Edge(int v, int next) : v(v), next(next) {}
} et[N << 1];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v) {
    et[tot] = Edge(v, eh[u]);
    eh[u] = tot++;
}

void dfs(int u, int fa, int deep) {
    dep[u] = deep;
    F[++rn] = u, B[rn] = deep, pos[u] = rn;
    st[u] = ++tot;
    father[u][0] = fa;
    for (int i = 1; i < M && father[u][i - 1]; i++) {
        father[u][i] = father[father[u][i - 1]][i - 1];
    }
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (v == fa) continue;
        dfs(v, u, deep + 1);
        F[++rn] = u, B[rn] = deep;
    }
    ed[u] = tot;
}

void Init_RMQ() {
    for (int i = 1; i <= rn; i++) rmq[i][0] = i;
    for (int j = 1; (1 << j) <= rn; j++) {
        for (int i = 1; i + (1 << j) - 1 <= rn; i++) {
            int a = rmq[i][j - 1], b = rmq[i + (1 << (j - 1))][j - 1];
            if (B[a] < B[b]) rmq[i][j] = a;
            else rmq[i][j] = b;
        }
    }
}

int RMQ(int a, int b) {
    int k = lg[b - a + 1];
    //int k = (int)(log(1.0 + b - a) / log(2.0));
    int u = rmq[a][k], v = rmq[b - (1 << k) + 1][k];
    if (B[u] < B[v]) return F[u];
    else return F[v];
}

int LCA(int a, int b) {
    a = pos[a], b = pos[b];
    if (a > b) swap(a, b);
    return RMQ(a, b);
}

pair<int, int> interval[6][10];
int alloc[6];

void insert(int id, int l, int r) {
    if (l <= r) interval[id][alloc[id]++] = pair<int, int>(l, r);
}

int get_kth_father(int u, int k) {
    for (int i = M - 1; i >= 0 && k; i--) {
        if (k >= (1 << i)) {
            u = father[u][i];
            k -= (1 << i);
        }
    }
    return u;
}

void handle(int a, int aid, int b, int bid) {
    int lca = LCA(a, b);
    if (dep[a] < dep[b]) {
        swap(a, b);
        swap(aid, bid);
    }
    //dep[a] >= dep[b]
    int len = dep[a] + dep[b] - 2 * dep[lca];
    if (len & 1) {
        int k = len / 2;
        int k_fa = get_kth_father(a, k);
        insert(aid, st[k_fa], ed[k_fa]);
        insert(bid, 1, st[k_fa] - 1);
        insert(bid, ed[k_fa] + 1, n);
    } else {
        if (dep[a] == dep[b]) {
            int k = len / 2 - 1, k_fa;
            k_fa = get_kth_father(a, k);
            insert(aid, st[k_fa], ed[k_fa]);
            k_fa = get_kth_father(b, k);
            insert(bid, st[k_fa], ed[k_fa]);
        } else {
            int k = len / 2 - 1;
            int k_fa = get_kth_father(a, k);
            insert(aid, st[k_fa], ed[k_fa]);
            k_fa = get_kth_father(k_fa, 1);
            insert(bid, 1, st[k_fa] - 1);
            insert(bid, ed[k_fa] + 1, n);
        }
    }
}

int calc(int a, int b) {
    int ans = 0;
    for (int i = 0; i < alloc[a]; i++) {
        for (int j = 0; j < alloc[b]; j++) {
            int c = max(interval[a][i].first, interval[b][j].first);
            int d = min(interval[a][i].second, interval[b][j].second);
            if (d >= c) ans += (d - c + 1);
        }
    }
    return ans;
}

void solve() {
    rn = tot = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < M; j++) {
            father[i][j] = 0;
        }
    }
    dfs(1, 0, 0);
    Init_RMQ();
    int a, b, c, m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        memset(alloc, 0, sizeof(alloc));
        handle(a, 0, b, 2);
        handle(a, 1, c, 4);
        handle(b, 3, c, 5);
        for (int j = 0; j < 3; j++) {
            int cnt = calc(j << 1, j << 1 | 1);
            printf("%d%c", cnt, j == 2 ? '\n' : ' ');
        }
    }
}

int main() {
    for (int i = 1; i < N << 1; i++) { lg[i] = int(log((double)i) / log(2.0)); }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) eh[i] = -1;
        tot = 0;
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            addedge(a, b);
            addedge(b, a);
        }
        solve();
    }
    return 0;
}
