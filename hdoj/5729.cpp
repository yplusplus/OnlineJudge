#include <iostream>
using namespace std;

const long long MOD = 1000000007LL;
const int N = 11;
long long dp[N][N];
long long f[N * N];
long long C[N][N];

void add(long long &a, long long b) {
    a += b;
    a %= MOD;
}

void sub(long long &a, long long b) {
    a += MOD - b;
    a %= MOD;
}

void mul(long long &a, long long b) {
    a *= b;
    a %= MOD;
}

int main() {
    
    C[0][0] = 1;
    for (int i = 1; i < N; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    f[0] = 1;
    for (int i = 1; i < N * N; i++) { f[i] = f[i - 1] * 3 % MOD; }

    for (int i = 0; i < N; i++) { dp[i][0] = dp[0][i] = 0; }
    dp[0][0] = dp[1][0] = dp[0][1] = 1;

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            dp[i][j] = f[i * j];
            for (int n = 0; n <= i - 1; n++) {
                for (int m = 0; m <= j; m++) {
                    if (n == i - 1 && m == j) continue;
                    long long tmp = 1;
                    mul(tmp, C[i - 1][n]);
                    mul(tmp, C[j][m]);
                    mul(tmp, dp[n + 1][m]);
                    mul(tmp, f[(i - 1 - n) * (j - m)]);
                    sub(dp[i][j], tmp);
                }
            }
        }
    }

    int n, m;
    while (cin >> n >> m) {
        cout << dp[n][m] << endl;
    }

    return 0;
}
