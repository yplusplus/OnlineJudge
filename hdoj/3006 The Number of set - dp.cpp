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
const int N = 111;
ll dp[1 << 14];
int s[N];
int n, m;
int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1, k; i <= n; i++) {
            s[i] = 0;
            scanf("%d", &k);
            for (int j = 0, x; j < k; j++) {
                scanf("%d", &x);
                s[i] |= (1 << --x);
            }
        }
        memset(dp, false, sizeof(dp));
        dp[0] = true;
        int all = 1 << m;
        for (int i = 1; i <= n; i++) {
            for (int mask = all - 1; mask >= 0; mask--) {
                dp[mask | s[i]] |= dp[mask];
            }
        }
        int ans = 0;
        for (int i = 1; i < all; i++) ans += dp[i];
        printf("%d\n", ans);
    }
    return 0;
}
