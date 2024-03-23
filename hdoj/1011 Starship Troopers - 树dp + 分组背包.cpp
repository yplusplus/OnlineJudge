#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
#include "cmath"
using namespace std;
#define pb push_back
#define maxn 105 
#define maxm 105
int n, m;
int bug[maxn], p[maxn];
int dp[maxn][maxm];
bool visit[maxn];
vector<int> g[maxn];

void init() {
    for(int i = 0; i < maxn; i++) g[i].clear();
    memset(dp, 0, sizeof(dp));
    memset(visit, false, sizeof(visit));
}

void dfs(int u) {
    visit[u] = true;
    int size = g[u].size();
    for(int i = 0; i < size; i++) {
        int v = g[u][i];
        if(visit[v]) continue;
        dfs(v);
        for(int j = m - bug[u]; j >= 0; j--)
            for(int k = 0; k <= j; k++) 
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k]);
    }
    for(int i = m; i >= bug[u]; i--) dp[u][i] = dp[u][i-bug[u]] + p[u];
    for(int i = bug[u] - 1; i >= 0; i--) dp[u][i] = 0;
    dp[u][0] = 0;
}

int main() {
    int u, v;
    while(~scanf("%d%d", &n, &m)) {
        if(n == -1 && m == -1) break;
        init();
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &bug[i], &p[i]);
            bug[i] = (bug[i] + 19) / 20;
        }
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v);
            g[u].pb(v);
            g[v].pb(u);
        }
        dfs(1);
        printf("%d\n", dp[1][m]);
    }
    return 0;
}
