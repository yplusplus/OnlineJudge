#pragma comment(linker, "/STACK:102400000,102400000")

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define mp make_pair
#define pb push_back

const int N = 111111;
const int M = 1111111;

vector<pair<int, int> > vec[N];
int n, m;

struct Edge {
    int u, v, w;
    void read() { scanf("%d%d%d", &u, &v, &w); }
    bool operator<(const Edge &e) const {
        return w < e.w;
    }
} edge[M];

struct UFS {
    int fa[N];
    void init() { for (int i = 0; i < N; i++) fa[i] = i; }
    int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
    bool Union(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return false;
        fa[ra] = rb;
        return true;
    }
} ufs;

int cnt[N];
long long dfs(int u, int fa) {
    long long res = 0;
    cnt[u] = 1;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first;
        if (v == fa) continue;
        res += dfs(v, u);
        res += (long long)vec[u][i].second * (n - cnt[v]) * cnt[v] * 2;
        cnt[u] += cnt[v];
    }
    return res;
}

void solve() {
    sort(edge, edge + m);
    ufs.init();
    for (int i = 1; i <= n; i++) vec[i].clear();
    long long mst_value = 0;
    for (int i = 0; i < m; i++) {
        if (ufs.Union(edge[i].u, edge[i].v)) {
            vec[edge[i].u].pb(mp(edge[i].v, edge[i].w));
            vec[edge[i].v].pb(mp(edge[i].u, edge[i].w));
            mst_value += edge[i].w;
        }
    }
    double ave = dfs(1, 0) * 1.0 / n / (n - 1);
    printf("%lld %.2f\n", mst_value, ave);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            edge[i].read();
        }
        solve();
    }
    return 0;
}

