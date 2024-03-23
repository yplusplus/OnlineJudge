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

const int N = 11111;
const int M = 111;
int dp[M][M], cost[N];
//dp[i][j] 表示第i个球染成黑色且倒数第二个黑球是i-j的最小代价
//实现时用了滚动数组
int n, m;
int main() {
    while(cin >> n >> m) {
        for(int i = 1; i <= n; i++) cin >> cost[i];
        fill(&dp[0][0], &dp[M][0], inf);
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j < i; j++) {
                dp[i][j] = cost[i] + cost[i-j];
                //cout << i << " " << j << " " << dp[i][j] << endl;
            }
        }
        for(int i = m + 1; i <= n; i++) {
            for(int j = 0; j <= m; j++) dp[i%M][j] = inf;
            for(int j = 1; j < m; j++) {
                if(i - j <= 0) break;
                for(int k = j + 1; k <= m; k++) {
                    if(i - k <= 0) break;
                    dp[i%M][j] = min(dp[i%M][j], dp[(i-j)%M][k-j] + cost[i]);
                    //cout << i << " " << j << " " << i - j << " " << k - j << " " << dp[i-j][k-j] << endl;
                }
                //cout << i << " " << j << " " << dp[i][j] << endl;
            }
        }
        int ans = inf;
        for(int i = 0; i < m; i++) {
            for(int j = i + 1; j < m; j++) {
                //cout << n - i << " " << n - j << endl;
                ans = min(ans, dp[(n-i)%M][j-i]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
