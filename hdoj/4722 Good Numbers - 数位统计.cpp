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

ll dp[20][10];
int digit[20];

ll dfs(int i, int sum, bool e) {
    if (i == -1) return sum == 0;
    if (!e && dp[i][sum] != -1) return dp[i][sum];
    ll res = 0;
    int u = e ? digit[i] : 9;
    for (int d = 0; d <= u; d++) {
        res += dfs(i - 1, (sum + d) % 10, e & (u == d));
    }
    return e ? res : dp[i][sum] = res;
}

ll calc(ll x) {
    if (x < 0) return 0;
    int tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    return dfs(tot - 1, 0, 1);
}

int main() {
    ios::sync_with_stdio(false);
    int T, Case = 1;
    cin >> T;
    memset(dp, -1, sizeof(dp));
    while (T--) {
        ll l, r;
        cin >> l >> r;
        cout << "Case #" << Case++ << ": ";
        cout << calc(r) - calc(l - 1) << endl;
    }
    return 0;
}
