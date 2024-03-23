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
const int N = 10;
const int M = 22;
int ones[1 << N], bit[M];
int dp[M][1 << N], stone[N];
int n, m;

int solve() {
    if (n == 1) {
        if (stone[0] == 0) return 0;
        else return -1;
    }
    memset(bit, 0, sizeof(bit));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < n; j++) {
            if (stone[j] >> i & 1) bit[i] |= 1 << j;
        }
        if (bit[i]) m = i + 1;
    }
    for (int i = 0; i <= m + 1; i++) {
        for (int j = 0; j < 1 << n; j++) {
            dp[i][j] = inf;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j < 1 << n; j++) {
            if (dp[i][j] == inf) continue;
            for (int k = 0; k < 1 << n; k++) {
                int nowState = bit[i] ^ j ^ k;
                int t = (j & k) + ((j ^ k) & bit[i]);
                if (~ones[nowState] & 1) {
                    dp[i + 1][t] = min(dp[i + 1][t], dp[i][j] + (ones[k] << i));
                }
            }
        }
    }
    int res = inf;
    for (int i = 0; i < 1 << n; i++) {
        if (~ones[i] & 1) {
            res = min(res, dp[m + 1][i]);
        }
    }
    return res;
}

int main() {
    ones[0] = 0;
    for (int mask = 1; mask < 1 << N; mask++) ones[mask] = ones[mask >> 1] + (mask & 1);
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) scanf("%d", &stone[i]);
        int ans = solve();
        if (ans == -1) puts("impossible");
        else printf("%d\n", ans);
    }
    return 0;
}
