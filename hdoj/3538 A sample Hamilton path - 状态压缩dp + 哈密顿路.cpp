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
const int N = 21;
int maz[N][N];
int n, m;
int first[N];
int dp[1 << N][N];

int solve() {
    if (first[0] != 0) return -1;
    int all = 1 << n;
    for (int mask = 0; mask < all; mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i] = inf;
        }
    }
    dp[1][0] = 0;
    for (int mask = 1; mask < all; mask++) {
        for (int i = 0; i < n; i++) {
            if (dp[mask][i] == inf) continue;
            for (int j = 0; j < n; j++) {
                if ((mask >> j & 1) || (maz[i][j] == -1)) continue;
                if ((first[j] & mask) != first[j]) continue;
                dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + maz[i][j]);
            }
        }
    }
    int ans = inf;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[all - 1][i]);
    }
    return ans == inf ? -1 : ans;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < n; i++) {
            first[i] = 0;
            for (int j = 0; j < n; j++) {
                scanf("%d", &maz[i][j]);
            }
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            first[b] |= (1 << a);
        }
        printf("%d\n", solve());
    }
    return 0;
}
