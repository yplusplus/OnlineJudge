#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1000000;
const int N = 55555;
const int M = 355;
int dp[M][M];
int ans[N];

void add(int &a, int b) { a = (a + b) % MOD; }

int main() {
    //dp[i][j] = dp[i - j][j] + dp[i - j][j - 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i < N; i++) {
        int now = i % 355;
        memset(dp[now], 0, sizeof(dp[now]));
        ans[i] = 0;
        for (int j = 1; j < M && j <= i; j++) {
            int next = (i - j) % 355;
            add(dp[now][j], dp[next][j]);
            if (j) add(dp[now][j], dp[next][j - 1]);
            if (j > 1) add(ans[i], dp[now][j]);
        }
    }
    ios::sync_with_stdio(false);
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        cout << ans[n] << endl;
    }
    return 0;
}
