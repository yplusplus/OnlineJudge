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

const int M = 555;
const int N = 22;
int dp[N][M];
vector<int> vec[N];
int n, k;
int main() {
    while (cin >> n >> k) {
        for (int i = 1; i <= n; i++) {
            vec[i].resize(k);
            for (int j = 0, x; j < k; j++) {
                cin >> vec[i][j];
            }
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < M; j++) {
                dp[i][j] = inf;
            }
        }
        for (int i = 0; i < k; i++) {
            dp[1][vec[1][i]] = 0;
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < k; j++) {
                for (int l = 0; l < M; l++) {
                    dp[i][vec[i][j]] = min(dp[i][vec[i][j]], dp[i-1][l] + abs(l - vec[i][j]));
                }
            }
        }
        int ans = inf;
        for (int i = 0; i < M; i++)  {
            ans = min(ans, dp[n][i]);
        }
        cout << ans << endl;
    }
    return 0;
}
