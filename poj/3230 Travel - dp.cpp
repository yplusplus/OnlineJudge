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
const int M = 111;
int cost[N][N];
int gain[M][N];
int dp[N][M];
int n, m;
int main() {
    while(~scanf("%d%d", &n, &m)) {
        if(!n && !m) break;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &cost[i][j]);
            }
        }
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &gain[i][j]);
            }
        }
        for(int i = 0; i <= m; i++)
            for(int j = 1; j <= n; j++)
                dp[i][j] = -inf;
        dp[0][1] = 0;
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                for(int k = 1; k <= n; k++) {
                    dp[i][j] = max(dp[i][j], dp[i-1][k] + gain[i][j] - cost[k][j]);
                }
            }
        }
        int ans = *max_element(dp[m], dp[m] + n + 1);
        printf("%d\n", ans);
    }
    return 0;
}
