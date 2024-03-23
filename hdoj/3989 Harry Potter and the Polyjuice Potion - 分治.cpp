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

int n;
int dp[1 << 20];
void solve(int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    solve(l, mid), solve(mid + 1, r);
    int len = r - mid;
    for (int i = mid + 1; i <= r; i++) {
        dp[i] += dp[i - len];
    }
}

int main() {
    while (scanf("%d", &n), n > 0) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            dp[x] += y;
        }
        solve(0, (1 << 20) - 1);
        printf("%d\n", *max_element(dp, dp + (1 << 20)));
    }
    return 0;
}
