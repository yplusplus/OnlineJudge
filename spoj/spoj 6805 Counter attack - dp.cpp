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
#define maxn 100050
int n, l0, l1, s0, s1;
int pass[2][maxn];
int draw[2][maxn];
int dp[2][maxn];
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d%d%d", &n, &l0, &l1, &s0, &s1);
        for(int i = 2; i <= n; i++)
            scanf("%d", &pass[0][i]);
        for(int i = 2; i <= n; i++)
            scanf("%d", &draw[0][i]);
        for(int i = 2; i <= n; i++)
            scanf("%d", &pass[1][i]);
        for(int i = 2; i <= n; i++)
            scanf("%d", &draw[1][i]);
        dp[0][1] = l0, dp[1][1] = l1;
        for(int i = 2; i <= n; i++) {
            dp[0][i] = min(dp[0][i-1] + draw[0][i], dp[1][i-1] + pass[1][i]);
            dp[1][i] = min(dp[1][i-1] + draw[1][i], dp[0][i-1] + pass[0][i]);
        }
        cout << min(dp[0][n] + s0, dp[1][n] + s1) << endl;
    }
    return 0;
}
