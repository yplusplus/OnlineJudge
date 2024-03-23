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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int MOD = 100000007;
int dp[2][2010][10];
int ans[1010][2010];
int n, m;

void init() {
    memset(dp, 0, sizeof(dp));
    dp[0][0][4] = 1;
    int p3 = 0, p2 = 1;
    for(int i = 1; i <= 1000; i++) {
        swap(p3, p2);
        for(int j = 0; j <= (i << 1); j++)
            for(int k = 0; k < 8; k++)
                dp[p3][j][k] = 0;
        for(int j = 0; j <= (i << 1); j++) {
            dp[p3][j][0] = (dp[p2][j][0] + dp[p2][j][2] + dp[p2][j][3] + dp[p2][j][4] + dp[p2][j][5]) % MOD;
            dp[p3][j][1] = (dp[p2][j][1] + dp[p2][j][2] + dp[p2][j][3] + dp[p2][j][4] + dp[p2][j][5] + dp[p2][j][6] + dp[p2][j][7]) % MOD;
            dp[p3][j][6] = dp[p3][j][7] = (dp[p2][j][0] + dp[p2][j][2] + dp[p2][j][3] + dp[p2][j][4] + dp[p2][j][5]) % MOD;
      //      dp[p3][j][7] = (dp[p2][j][0] + dp[p2][j][2] + dp[p2][j][3] + dp[p2][j][4] + dp[p2][j][5]) % MOD;
            if(j >= 1) {
                dp[p3][j][3] = dp[p3][j][2] = (dp[p2][j-1][1] + dp[p2][j-1][2] + dp[p2][j-1][3] + dp[p2][j-1][4] + dp[p2][j-1][5] + dp[p2][j-1][6] + dp[p2][j-1][7]) % MOD;
        //        dp[p3][j][3] = (dp[p2][j-1][1] + dp[p2][j-1][2] + dp[p2][j-1][3] + dp[p2][j-1][4] + dp[p2][j-1][5] + dp[p2][j-1][6] + dp[p2][j-1][7]) % MOD;
                dp[p3][j][4] = (dp[p2][j-1][0] + dp[p2][j-1][2] + dp[p2][j-1][3] + dp[p2][j-1][4] + dp[p2][j-1][5]) % MOD;
            }
            if(j >= 2) dp[p3][j][5] = (dp[p2][j-2][1] + dp[p2][j-2][2] + dp[p2][j-2][3] + dp[p2][j-2][4] + dp[p2][j-2][5] + dp[p2][j-2][6] + dp[p2][j-2][7]) % MOD;
            ans[i][j] = (dp[p3][j][4] + dp[p3][j][5]) % MOD;
        } 
    }
}

int main() {
    int T;
    init();
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        printf("%d\n", ans[n][m]);
    }
    return 0;
}
