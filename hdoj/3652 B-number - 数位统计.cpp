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
int dp[N][3][13];
int digit[N], tot;
int newState(int now, int x) {
    if (now == 2) return 2;
    if (now == 1 && x == 3) return 2;
    if (x == 1) return 1;
    return 0;
}

int dfs(int i, int s, int r, bool e) {
    if (i == -1) return s == 2 && (r % 13 == 0);
    if (!e && ~dp[i][s][r]) return dp[i][s][r];
    int res = 0;
    int u = e ? digit[i] : 9;
    for (int d = 0; d <= u; d++) {
        res += dfs(i - 1, newState(s, d), (r * 10 + d) % 13, e & (u == d));
    }
    return e ? res : dp[i][s][r] = res;
}

int calc(int x) {
    tot = 0;
    while (x) {
        digit[tot++] = x % 10;
        x /= 10;
    }
    return dfs(tot - 1, 0, 0, 1);
}

int main() {
    memset(dp, -1, sizeof(dp));
    int n;
    while (cin >> n) {
        cout << calc(n) << endl;
    }
    return 0;
}
