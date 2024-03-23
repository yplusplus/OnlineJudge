#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
double dp[60];
int n, s;
double sum;
int main() {
    while(~scanf("%d%d", &n, &s)) {
        memset(dp, 0, sizeof(dp));
        dp[s] = 1.0, sum = 0.0;
        for(int i = 1; i <= n; i++) 
            for(int j = 0; j <= s; j++)
                dp[j] = dp[j] * 2 / 3 + dp[j+1] / 3;
        for(int i = 0; i <= s; i++) sum += dp[i];
        double ans = 100.0 * (sum - dp[0]) / sum;
        printf("%.5f\n", ans);
    }
    return 0;
}

