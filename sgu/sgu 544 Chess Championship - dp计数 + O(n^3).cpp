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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 510;
int dp[2][N][N];
int a[N], b[N];
const int MOD = 1000000009;

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    b = max(b, 0);
    return 1LL * a * b % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    int n, k;
    while (cin >> n >> k) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        sort(a, a + n);
        sort(b, b + n);
        memset(dp[0], 0, sizeof(dp[0]));
        dp[0][0][0] = 1;
        int p = 0, q = 0;
        for (int i = 0; i < 2 * n; i++) {
            int now = i & 1;
            int next = now ^ 1;
            //memset(dp[next], 0, sizeof(dp[next]));
            for (int j = 0; j <= i / 2; j++) {
                for (int k = 0; k <= i / 2; k++) {
                    dp[next][j][k] = 0;
                }
            }
            int who = -1;
            if (p < n && q < n) {
                if (a[p] < b[q]) who = 0, p++;
                else who = 1, q++;
            } else if (p < n) who = 0, p++;
            else who = 1, q++;
            for (int j = 0; j <= i / 2; j++) {
                for (int k = 0; k <= i / 2; k++) {
                    dp[next][j][k] = add(dp[next][j][k], dp[now][j][k]);
                    if (who == 0) {
                        dp[next][j + 1][k] = add(dp[next][j + 1][k], mul(dp[now][j][k], (q - j - k)));
                    } else {
                        dp[next][j][k + 1] = add(dp[next][j][k + 1], mul(dp[now][j][k], (p - j - k)));
                    }
                }
            }
        }
        int ans = 0;
        if ((n + k) % 2 == 0) ans = dp[0][(n + k) / 2][(n - k) / 2];
        cout << ans << endl;
    }
    return 0;
}
