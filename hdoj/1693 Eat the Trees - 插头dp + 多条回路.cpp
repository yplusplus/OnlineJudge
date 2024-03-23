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

int n, m;
ll dp[13][13][1<<13];
bool maz[13][13];

void solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][m][0] = 1;
    int nn = 1 << m << 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < nn; j++)
            dp[i][0][j<<1] = dp[i-1][m][j];
        for(int j = 1; j <= m; j++) {
            for(int k = 0; k < nn; k++) {
                int p = 1 << j;
                int q = p >> 1;
                bool dw = p & k;//ÏÂ²åÍ·
                bool ri = q & k;//ÓÒ²åÍ·
                if(maz[i][j]) {
                    if(dw && ri) dp[i][j][k] = dp[i][j-1][k^p^q];
                    else if(dw || ri) dp[i][j][k] = dp[i][j-1][k] + dp[i][j-1][k^p^q];
                    else dp[i][j][k] = dp[i][j-1][k^p^q];
                } else {
                    if(dw || ri) dp[i][j][k] = 0;
                    else dp[i][j][k] = dp[i][j-1][k];
                }
            }
        }
    }
    printf("There are %I64d ways to eat the trees.\n", dp[n][m][0]);
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                scanf("%d", &maz[i][j]);
            }
        }
        printf("Case %d: ", Case++);
        solve();
    }
    return 0;
}
