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

const int inf = 1 << 30;
#define MAX 100050
int dp[13][MAX], n;
int main() {
    while(~scanf("%d", &n), n) {
        int T = 0, x, t;
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < 13; i++) dp[i][0] = -inf;
        dp[6][0] = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &x, &t);
            dp[x+1][t]++;
            T = max(T, t);
        }
        for(int i = 1; i <= T; i++)
            for(int j = 1; j <= 11; j++)
                dp[j][i] += max(dp[j-1][i-1], max(dp[j][i-1], dp[j+1][i-1]));
        int ans = 0;
        for(int i = 1; i <= 11; i++) ans = max(ans, dp[i][T]);
        cout << ans << endl;
    }
    return 0;
}
