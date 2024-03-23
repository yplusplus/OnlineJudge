#include <iostream>
#include <cstdio>
using namespace std;

const int N = 1111;
const int MOD = 10056;
int dp[N][N];
int ans[N];
int main() {
    dp[0][0] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = (dp[i - 1][j - 1] * j + dp[i - 1][j] * j) % MOD;
            (ans[i] += dp[i][j]) %= MOD;
        }
    }
    int T, Case = 1, n;
    cin >> T;
    while (T--) {
        cin >> n;
        printf("Case %d: %d\n", Case++, ans[n]);
    }
    return 0;
}
