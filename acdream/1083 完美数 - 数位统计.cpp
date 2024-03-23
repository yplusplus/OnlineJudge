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
const int N = 40;
int dp[N][4];
int digit[N];
int tot;
//0 none
//1 only has 3
//2 only has 8
//3 both 3 and 8
int newState(int now, int x) {
    if (x == 3) return now | 1;
    if (x == 8) return now | 2;
    return now;
}

int dfs(int i, int s, bool e) {
    if (i == -1) return s == 1 || s == 2;
    if (!e && ~dp[i][s]) return dp[i][s];
    int u = e ? digit[i] : 9;
    int res = 0;
    for (int d = 0; d <= u; d++) {
        res += dfs(i - 1, newState(s, d), e && (u == d));
    }
    return e ? res : dp[i][s] = res;
}

int calc(int x) {
    tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    return dfs(tot - 1, 0, 1);
}

int main() {
    memset(dp, -1, sizeof(dp));
    int T;
    cin >> T;
    while (T--) {
        int l, r;
        cin >> l >> r;
        int ans = calc(r) - calc(l - 1);
        //cout << calc(r) << endl;
        //cout << calc(l - 1) << endl;
        cout << ans << endl;
    }
    return 0;
}
