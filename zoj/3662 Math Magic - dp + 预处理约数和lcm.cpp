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
const int MOD = 1000000007;
int n, m, k;
int dp[1111][33];
int LCM[33][33];
int id[1111];
inline int __gcd(int a, int b) {
    return a % b == 0 ? b : __gcd(b, a % b);
}
inline int __lcm(int a, int b) {
    return a * b / __gcd(a, b);
}

int main() {
    while(~scanf("%d%d%d", &n, &m, &k)) {
        vector<int> vec;
        int tot = 0;
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= m; i++) {
            if(m % i == 0) {
                vec.pb(i);
                id[i] = tot++;
            }
        }
        for(int i = 0; i < tot; i++) {
            for(int j = 0; j < tot; j++) {
                LCM[i][j] = id[__lcm(vec[i], vec[j])];
            }
        }
        for(int i = 0; i < tot; i++) dp[vec[i]][i] = 1;
        for(int i = 1; i < k; i++) {
            for(int sum = n; sum > 0; sum--) {
                for(int lcm = 0; lcm < tot; lcm++) {
                    if(dp[sum][lcm] == 0) continue;
                    for(int ii = 0; ii < vec.size(); ii++) {
                        int nextSum = sum + vec[ii];
                        if(nextSum > n) break;
                        int nextLCM = LCM[lcm][ii];
                        dp[nextSum][nextLCM] += dp[sum][lcm];
                        if(dp[nextSum][nextLCM] >= MOD) dp[nextSum][nextLCM] -= MOD;
                    }
                    dp[sum][lcm] = 0;
                }
            }
        }
        printf("%d\n", dp[n][id[m]]);
    }
    return 0;
}
