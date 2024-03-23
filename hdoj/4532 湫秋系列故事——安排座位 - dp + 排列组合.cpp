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
const int N = 50;
const int M = 455;
const ll MOD = 1000000007LL;
ll dp[N][M];
int a[N];
ll fac[N], bin[M][M];

int n;
ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

int main() {
    int T, Case = 1;
    cin >> T;
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = mul(fac[i - 1], i);
    for (int i = 0; i < M; i++) {
        bin[i][0] = bin[i][i] = 1;
        for (int j = 0; j < i; j++) {
            bin[i][j] = add(bin[i - 1][j - 1], bin[i - 1][j]);
        }
    }
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        memset(dp, 0, sizeof(dp));
        int sum = a[0];
        dp[0][a[0] - 1] = 1;
        for (int i = 1; i < n; i++){
            for (int j = 0; j < sum; j++) {
                int u = min(a[i], sum + 1);
                for (int k = 1; k <= u; k++) {
                    for (int l = 0; l <= k && l <= j; l++) {
                        ll tmp = mul(mul(dp[i - 1][j], bin[j][l]), mul(bin[sum + 1 - j][k - l], bin[a[i] - 1][k - 1]));
                        dp[i][j - l + a[i] - k] = add(dp[i][j - l + a[i] - k], tmp);
                    }
                }
            }
            sum += a[i];
        }
        ll ans = dp[n - 1][0];
        for (int i = 0; i < n; i++) {
            ans = mul(ans, fac[a[i]]);
        }
        printf("Case %d: %d\n", Case++, (int)ans);
    }
    return 0;
}
