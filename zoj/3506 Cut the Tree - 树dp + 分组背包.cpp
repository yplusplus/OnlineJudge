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
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 1010
const int inf = 1 << 26;
vector<int> vec[maxn];
int val[maxn];
int dp[maxn][25][2];
int n, k;
int cnt[maxn];
int dfs(int u, int fa) {
    cnt[u] = 1;
    int size = vec[u].size();
    dp[u][0][0] = dp[u][0][1] = 0;
    for(int i = 1; i <= k; i++) {
        dp[u][i][0] = inf;
        dp[u][i][1] = -inf;
    }
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        cnt[u] += dfs(v, u);
        for(int j = k; j >= 0; j--) {
            dp[u][j][0] += dp[v][0][0];
            dp[u][j][1] += dp[v][0][1];
            for(int jj = 1; jj <= j; jj++) {
                dp[u][j][0] = min(dp[u][j][0], dp[u][j-jj][0] + dp[v][jj][0]);
                dp[u][j][1] = max(dp[u][j][1], dp[u][j-jj][1] + dp[v][jj][1]);
            }
            for(int jj = 0; jj < cnt[v] && jj < j; jj++) {
                dp[u][j][0] = min(dp[u][j][0], dp[u][j-jj-1][0]);
                dp[u][j][1] = max(dp[u][j][1], dp[u][j-jj-1][1]);
            }
        }
    }
    for(int i = 0; i <= k; i++) {
        dp[u][i][0] += val[u];
        dp[u][i][1] += val[u];
    }
    return cnt[u];
}

void solve() {
    memset(cnt, 0, sof(cnt));
    dfs(1, -1);
    int ans1 = dp[1][k][0], ans2 = dp[1][k][1];
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= k && n - cnt[i] >= j ; j++) {
            ans1 = min(ans1, dp[i][k-j][0]);
            ans2 = max(ans2, dp[i][k-j][1]);
        }
    }
    cout << ans1 << " " << ans2 << endl;
}

int main() {
    while(cin >> n >> k) {
        for(int i = 1; i <= n; i++) {
            cin >> val[i];
            vec[i].clear();
        }
        int a, b;
        for(int i = 1; i < n; i++) {
            cin >> a >> b;
            vec[a].pb(b);
            vec[b].pb(a);
        }
        solve();
    }
    return 0;
}
