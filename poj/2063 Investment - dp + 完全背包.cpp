#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

int ans, n, cnt;
int w[15], v[15];
int dp[100050];

void solve() {
    for(int i = 0; i < cnt; i++) {
        memset(dp, 0, sizeof(dp));
        for(int j = 1; j <= n; j++) {
            for(int k = w[j]; k <= ans / 1000; k++) {
                dp[k] = max(dp[k], dp[k-w[j]] + v[j]);
            }
        }
     //   cout << dp[ans/1000] << endl;
        ans += dp[ans/1000];
    }
    printf("%d\n", ans);
}


int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &ans, &cnt);
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &w[i], &v[i]);
            w[i] /= 1000;
        }
        solve();
    }
    return 0;
}
