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
const int N = 111;
const int M = 1111;
int dp[2][N][M];
int n, m;
int a, b;
int main() {
    while (cin >> n >> m) {
        memset(dp[0], -1, sizeof(dp[0]));
        dp[0][0][0] = 0;
        for (int i = 0, x, y; i < n; i++) {
            int p = i & 1;
            int q = p ^ 1;
            cin >> x >> y;
            memset(dp[q], -1, sizeof(dp[q]));
            for (int j = 0; j <= i; j++) {
                for (int k = 0; k < M; k++) {
                    if (dp[p][j][k] >= 0) {
                        dp[q][j][k] = max(dp[q][j][k], dp[p][j][k]);
                        dp[q][j + 1][k + x] = max (dp[q][j + 1][k + x], dp[p][j][k] + y);
                    }
                }
            }
        }
        int ans = -1;
        cin >> a >> b;
        for (int i = a; i < M; i++) {
            if (dp[n & 1][m][i] >= b) ans = max(ans, i - a + dp[n & 1][m][i] - b);
        }
        cout << ans << endl;
    }
    return 0;
}
