#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int C = 111;
double dp[2][C];

int main() {
    int c, n, m;
    while (scanf("%d", &c), c) {
        scanf("%d%d", &n, &m);
        if (m > c || ((n - m) % 2 == 1)) {
            puts("0.000");
            continue;
        }
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1.0;
        if (n > 5000) n = 5000 + (n & 1);
        for (int i = 0; i < n; i++) {
            int x = i & 1, y = x ^ 1;
            for (int j = 0; j <= c; j++) { dp[y][j] = 0.0; }
            for (int j = 0; j <= c; j++) {
                dp[y][j - 1] += dp[x][j] * j / c;
                dp[y][j + 1] += dp[x][j] * (c - j) / c;
            }
        }
        double ans = dp[n & 1][m];
        printf("%.3f\n", ans);
    }
    return 0;
}
