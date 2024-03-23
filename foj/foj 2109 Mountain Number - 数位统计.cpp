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

int digit[20];
ll dp[20][20][2];

ll dfs(int i, int pre, bool s, bool e, bool t) {
    if (i == -1) return 1LL;
    if (!e && ~dp[i][pre][s]) return dp[i][pre][s];
    ll res = 0;
    int u = e ? digit[i] : 9;
    for (int d = 0; d <= u; d++) {
        if (!s) {
            if (d >= pre) {
                if (!t) res += dfs(i - 1, d, s ^ 1, e && (u == d), 0);
                else if (d == 0) res += dfs(i - 1, d, 0, e && (u == d), 1);
                else if (d > 0) res += dfs(i - 1, d, 0, e && (u == d), 0);
            }
        } else {
            if (d <= pre) {
                res += dfs(i - 1, d, s ^ 1, e && (u == d), 0);
            }
        }
    }
    return e ? res : dp[i][pre][s] = res;
}

ll calc(ll x) {
    int tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    return dfs(tot - 1, 0, 0, 1, 1);
}
int main() {
    int T;
    cin >> T;
    memset(dp, -1, sizeof(dp));
    while (T--) {
        ll l, r;
        cin >> l >> r;
        cout << calc(r) - calc(l - 1) << endl;
    }
    return 0;
}
