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
ll dp[N][N];
ll sum[N][N];
int main() {
    int T, Case;
    cin >> T;
    int n;
    while (cin >> Case >> n) {
        ll ans = 0;
        if (n == 1) {
            cout << Case << " " << 1 << endl;
            continue;
        }
        memset(dp, 0, sizeof(dp));
        memset(sum, 0, sizeof(sum));
        dp[1][1] = sum[1][1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if (~i & 1) dp[i][j] = sum[i-1][j-1];
                else dp[i][j] = sum[i-1][i-1] - sum[i-1][j-1];
                sum[i][j] = sum[i][j-1] + dp[i][j];
            }
        }
        cout << Case << " " << sum[n][n] * 2 << endl;
        
    }
    return 0;
}
