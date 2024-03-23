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
const int N = 22;
int n;
ll dp[N][3];
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        memset(dp, 0, sizeof(dp));
        dp[1][0] = dp[1][1] = dp[1][2] = 1;
        //left up right
        for (int i = 2; i <= n; i++) {
            dp[i][0] = dp[i-1][0] + dp[i-1][1];
            dp[i][1] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2];
            dp[i][2] = dp[i-1][1] + dp[i-1][2];
        }
        cout << dp[n][0] + dp[n][1] + dp[n][2] << endl;
    }
    return 0;
}
