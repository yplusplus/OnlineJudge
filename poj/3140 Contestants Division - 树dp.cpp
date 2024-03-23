#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
using namespace std;
#define pb push_back
#define ll long long
#define maxn 100050
vector<int> vec[maxn];
const ll inf = 100000000000000LL;
int n, m;
ll val[maxn], dp[maxn], sum, ans;

ll ABS(ll x) {
    return (x > 0) ? x : (-x);
}

void dfs(int u, int fa) {
    int size = vec[u].size();
    dp[u] = val[u];
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dfs(v, u);
        dp[u] += dp[v];
        ans = min(ABS(sum - 2 * dp[v]), ans);
    }
}

int main() {
    int Case = 1, u, v;
    while(~scanf("%d%d", &n, &m)) {
        if(!n && !m) break;
        for(int i = 0; i < maxn; i++) vec[i].clear();
        ans = inf, sum = 0;
        for(int i = 1; i <= n; i++) { 
            scanf("%lld", &val[i]);
            sum += val[i];
        }
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            vec[u].pb(v), vec[v].pb(u);
        }
        dfs(1, -1);
        printf("Case %d: %lld\n", Case++, ans);
    }
    return 0;
}
