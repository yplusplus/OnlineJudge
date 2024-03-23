#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 2222;
int dp[N][N];
vector<int> vec[N];
int n;
int w[N], cnt[N];
void dfs(int u, int fa) {
    dp[u][0] = 0;
    cnt[u] = 1;
    dp[u][1] = w[u];
    for(int i = 2; i <= n; i++) dp[u][i] = inf;
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dfs(v, u);
        cnt[u] += cnt[v];
        for(int j = cnt[u]; j >= 2; j--) {
            for(int k = 0; k <= j - 1 && k <= cnt[v]; k++) {
                dp[u][j] = min(dp[u][j], dp[u][j-k] + dp[v][k]);
            }
        }
    }
}

int main() {
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; i++) {
            scanf("%d", &w[i]);
            vec[i].clear();
        }
        for(int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            vec[b].pb(a);
        }
        dfs(1, -1);
        for(int i = 1; i <= n; i++) {
            int ans = inf;
            for(int j = 1; j <= n; j++) {
                ans = min(ans, dp[j][i]);
            }
            printf("%d%c", ans, i == n ? '\n' : ' ');
        }
    }
    return 0;
}
