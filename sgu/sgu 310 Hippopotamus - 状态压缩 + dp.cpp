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
const int N = 66;
ll dp[N][1<<14];
int sum[1<<14];
int n, m, k;
//dp
//dp[i][j] 表示已经选择好前i个，且最后m-1个情况为j的方案数

int main() {
    while(cin >> n >> m >> k) {
        if(m == 1) {
            if(k == 1) cout << 1 << endl;
            else cout << (1LL << n) << endl;
            continue;
        }
        memset(dp, 0, sizeof(dp));
        int all = 1 << (m - 1);
        int MM = all - 1;
        sum[0] = 0;
        for(int mask = 1; mask < all; mask++) {
            int j = 0;
            while(~mask >> j & 1) j++;
            sum[mask] = sum[mask ^ (1 << j)] + 1;
        }

        for(int mask = 0; mask < all; mask++) {
            if(sum[mask] < k - 1) continue;
            dp[m-1][mask] = 1;
        }
        for(int i = m - 1; i < n; i++) {
            for(int mask = 0; mask < all; mask++) {
                if(!dp[i][mask]) continue;
                int cnt = sum[mask];
                if(cnt + 1 == k) {
                    dp[i+1][(mask << 1 | 1) & MM] += dp[i][mask];
                } else if(cnt + 1 > k) {
                    dp[i+1][(mask << 1 | 1) & MM] += dp[i][mask];
                    dp[i+1][(mask << 1) & MM] += dp[i][mask];
                }
            }
        }
        ll ans = 0;
        for(int i = 0; i < all; i++)
            ans += dp[n][i];
        cout << ans << endl;
    }
    return 0;
}
