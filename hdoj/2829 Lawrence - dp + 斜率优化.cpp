#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

typedef long long LL;

const int N = 1111;
const int M = 1111;
int n, m;
LL sum[N], sum2[N];
LL dp[M][N];
int que[N], head, tail;

bool check(int i, int j, int k, int m) {
    LL Xi = sum[i], Yi = 2 * dp[m][i] + sum[i] * sum[i] + sum2[i];
    LL Xj = sum[j], Yj = 2 * dp[m][j] + sum[j] * sum[j] + sum2[j];
    LL Xk = sum[k], Yk = 2 * dp[m][k] + sum[k] * sum[k] + sum2[k];
    return (Yj - Yi) * (Xk - Xj) >= (Yk - Yj) * (Xj - Xi);
}

// dp[m][j] -> dp[m + 1][i]
LL calc(int i, int j, int m) {
    return dp[m][j] + ((sum[i] - sum[j]) * (sum[i] - sum[j]) - (sum2[i] - sum2[j])) / 2;
}

void solve() {
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = calc(j, 0, 0);
            } else {
                while (tail - head >= 2 && que[head + 1] < j 
                        && calc(j, que[head], i - 1) >= calc(j, que[head + 1], i - 1))
                {
                    head++;
                }
                assert(head < tail);
                dp[i][j] = calc(j, que[head], i - 1);
            }
        }
        head = tail = 0;
        for (int j = 0; j <= n; j++) {
            while (tail - head >= 2 && check(que[tail - 2], que[tail - 1], j, i))
                tail--;
            que[tail++] = j;
        }
    }
    cout << dp[m][n] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        if (!n && !m) break;
        sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> sum[i];
            sum2[i] = sum[i] * sum[i] + sum2[i - 1];
            sum[i] += sum[i - 1];
        }
        solve();
    }
    return 0;
}
