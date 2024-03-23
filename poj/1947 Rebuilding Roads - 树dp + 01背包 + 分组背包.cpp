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
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 155
const int inf = 1 << 25;
vector<int> vec[maxn];
int dp[maxn][maxn];
bool visit[maxn];
int n, p;

void dfs(int u) {
    int size = vec[u].size();
    fill(&dp[u][0], &dp[u][maxn], inf);
    dp[u][1] = 0;
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        dfs(v);
        for(int j = p; j >= 1; j--) {
            dp[u][j]++;
            for(int k = 1; k < j; k++) {
                dp[u][j] = min(dp[u][j], dp[u][j-k] + dp[v][k]);
            } 
        }
    }
}

int main() {
    int u, v, root;
    while(~scanf("%d%d", &n, &p)) {
        memset(visit, true, sizeof(visit));
        for(int i = 0; i <= n; i++) vec[i].clear();
        for(int i = 0; i < n - 1; i++) {
            scanf("%d%d", &u, &v);
            vec[u].pb(v);
            visit[v] = false;
        }
        for(int i = 1; i <= n; i++)
            if(visit[i]) root = i;
        dfs(root);
        int ans = dp[root][p];
        for(int i = 1; i <= n; i++)
            ans = min(ans, dp[i][p] + 1);
        cout << ans << endl;
    }
    return 0;
}
