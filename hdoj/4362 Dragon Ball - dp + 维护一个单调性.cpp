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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
int n, m, x;
pii ball[55][1010];
int dp[55][1010];
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &m, &n, &x);
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++)
                dp[i][j] = inf;
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++)
                scanf("%d", &ball[i][j].fi);
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++)
                scanf("%d", &ball[i][j].se);
            sort(ball[i] + 1, ball[i] + 1 + n);
        }
        for(int i = 1; i <= n; i++) {
            dp[1][i] = ball[1][i].se + abs(ball[1][i].fi - x);
        }
        int res, p, sum;
        for(int i = 2; i <= m; i++) {
            p = 1;
            sum = 0;
            res = inf;
            for(int j = 1; j <= n; j++) {
                if(j > 1) sum += ball[i][j].fi - ball[i][j-1].fi;
                while(p <= n && ball[i-1][p].fi <= ball[i][j].fi) {
                    res = min(res, dp[i-1][p] + ball[i][j].fi - ball[i-1][p].fi - sum);
                    p++;
                }
                dp[i][j] = min(dp[i][j], res + sum + ball[i][j].se);
            }
            sum = 0;
            p = n;
            res = inf;
            for(int j = n; j; j--) {
                if(j < n) sum += ball[i][j+1].fi - ball[i][j].fi;
                while(p && ball[i-1][p].fi >= ball[i][j].fi) {
                    res = min(res, dp[i-1][p] + ball[i-1][p].fi - ball[i][j].fi - sum);
                    p--;
                }
                dp[i][j] = min(dp[i][j], res + sum + ball[i][j].se);
            }
        }
        int ans = *min_element(dp[m] + 1, dp[m] + 1 + n);
        printf("%d\n", ans);
    }
    return 0;
}
