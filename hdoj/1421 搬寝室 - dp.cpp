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
const int N = 2222;
const int K = 1111;
int a[N];
int dp[N][K];
int n, k;
int sq(int x) {
    return x * x;
}

int main() {
    while (cin >> n >> k) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + n + 1);
        for (int i = 0; i < N; i++) {
            for (int j = 1; j < K; j++) {
                dp[i][j] = inf;
            }
            dp[i][0] = 0;
        }
        a[0] = (int)sqrt(inf);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = min(dp[i-2][j-1] + sq(a[i] - a[i-1]), dp[i-1][j]);
            }
        }
        printf("%d\n", dp[n][k]);
    }
    return 0;
}
