#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 1010
const int inf = 1 << 20;
int n, m, limit;
int dp[maxn];
struct Edge {
    int v, w;
    Edge(){}
    Edge(int _v, int _w) {
        v = _v, w = _w;
    }
};
vector<Edge> vec[maxn];

void dfs(int u, int fa) {
    dp[u] = 0;
    int size = vec[u].size();
    for(int i = 0; i < size; i++) {
        int v = vec[u][i].v, w = vec[u][i].w;
        if(v == fa) continue;
        if(w > limit) w = inf;
        dfs(v, u);
        dp[u] += min(dp[v], w);
    }
    if(!dp[u]) dp[u] = inf;
}

void solve() {
    int ans = -1;
    int l = 1, r = 1000;
    while(l <= r) {
        int mid = (l + r) >> 1;
        limit = mid;
        dfs(1, -1);
        if(dp[1] <= m) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans << endl;
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        if(!n) break;
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 1; i < n; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            vec[u].pb(Edge(v, w));
            vec[v].pb(Edge(u, w));
        }
        solve();
    }
    return 0;
}
