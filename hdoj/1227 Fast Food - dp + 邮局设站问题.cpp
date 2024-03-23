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

const int N = 222;
const int K = 33;
int d[N];
int dp[K][N];
int cost[N][N];
int main() {
    int n, k;
    int Case = 1;
    while (~scanf("%d%d", &n, &k)) {
        if (n == 0) break;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &d[i]);
        }
        memset(cost, 0, sizeof(cost));
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                int x = (j + 1 - i) / 2 + i;
                for (int k = i; k <= j; k++) {
                    cost[i][j] += abs(d[x] - d[k]);
                }
            }
        }
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = inf;
            }
        }
        dp[0][0] = 0;
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                for (int l = 0; l < j; l++) {
                    dp[i][j] = min(dp[i][j], dp[i-1][l] + cost[l+1][j]);
                }
            }
        }
        printf("Chain %d\n", Case++);
        printf("Total distance sum = %d\n\n", dp[k][n]);
    }
    return 0;
}
