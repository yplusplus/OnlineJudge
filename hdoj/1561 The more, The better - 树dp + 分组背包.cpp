#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;
#define pb push_back
#define maxn 205
#define maxm 205
int n, m;
vector<int> g[maxn];
int dp[maxn][maxm], val[maxn];

void init() {
    for(int i = 0; i < maxn; i++) g[i].clear();
    memset(dp, 0, sizeof(dp));
}

void dfs(int u) {
    int size = g[u].size();
    for(int i = 0; i < size; i++) {
        int v = g[u][i];
        dfs(v);
        for(int j = m; j >= 0; j--)
            for(int k = 0; k <= j; k++)
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k]);
    }
    for(int j = m + 1; j >= 1; j--) dp[u][j] = dp[u][j-1] + val[u];
    cout << dp[u][0] << endl;
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        if(!n && !m) break;
        init();
        for(int i = 1; i <= n; i++) {
            int u;
            scanf("%d%d", &u, &val[i]);
            g[u].pb(i);
        }
        dfs(0);
        printf("%d\n", dp[0][m+1]);
    }
    return 0;
}
