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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111111;
vector<int> vec[N];
int dp[1111][1111];
int val[N];
int n, k;

void dfs(int u, int dep) {
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        for (int j = 0; j <= k; j++) dp[dep + 1][j] = dp[dep][j];
        dfs(v, dep + 1);
        for (int j = k; j >= 1; j--) {
            dp[dep][j] = max(dp[dep][j - 1] + val[v], dp[dep + 1][j]);
            if (dp[dep][j] < 0) dp[dep][j] = -inf;
        }
    }
}

int main() {
    while (~scanf("%d%d", &n, &k), n + k) {
        for (int i = 0; i <= n; i++) vec[i].clear();
        for (int i = 1; i <= n; i++) {
            int p;
            scanf("%d%d", &p, &val[i]);
            vec[p].pb(i);
        }
        for (int i = 1; i <= k; i++) dp[0][i] = -inf;
        dp[0][0] = 0;
        dfs(0, 0);
        if (dp[0][k] < 0) dp[0][k] = 0;
        printf("%d\n", dp[0][k]);
    }
    return 0;
}
