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

const int N = 1111;
int f[N], dp[N][N], sum[N];
int n, m, l;
int main() {
    while (~scanf("%d%d%d", &n, &m, &l)) {

        sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &sum[i]);
            sum[i] += sum[i - 1];
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = -inf;
            }
            f[i] = -inf;
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            if (i - l >= 0) {
                for (int j = 0; j <= i; j++) f[j] = max(f[j], dp[i - l][j] - sum[i - l]);
            }
            for (int j = 0; j <= i; j++) {
                if (j >= 1) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
                dp[i][j] = max(dp[i][j], f[j] + sum[i]);
            }
        }

        int ans = -inf;
        for (int i = m; i <= n; i++) ans = max(ans, dp[n][i]);
        printf("%d\n", ans);
    }
    return 0;
}
