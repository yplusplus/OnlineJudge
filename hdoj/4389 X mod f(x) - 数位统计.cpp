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

int dp[83][83][83][11];
int digit[11];
int dfs(int i, int sum, int target_sum, int r, bool e) {
    if (sum > target_sum) return 0;
    if (i == -1) {
        return sum == target_sum && r == 0;
    }
    if (!e && ~dp[target_sum][sum][r][i]) return dp[target_sum][sum][r][i];
    int u = e ? digit[i] : 9;
    int res = 0;
    for (int d = 0; d <= u; d++) {
        res += dfs(i - 1, sum + d, target_sum, (r * 10 + d) % target_sum, e && (u == d));
    }
    return e ? res : dp[target_sum][sum][r][i] = res;
}

int calc(ll x) {
    int tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    int res = 0;
    for (int i = 1; i < 83; i++) {
        res += dfs(tot - 1, 0, i, 0, 1);
    }
    return res;
}

int main() {
    int T, Case = 1;
    cin >> T;
    memset(dp, -1, sizeof(dp));
    while (T--) {
        ll l, r;
        cin >> l >> r;
        printf("Case %d: %d\n", Case++, calc(r) - calc(l - 1));
    }
    return 0;
}
