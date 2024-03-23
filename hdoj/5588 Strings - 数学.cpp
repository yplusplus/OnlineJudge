#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int M = 66;

long long n, m;
long long dp[M];

int main() {
    while (cin >> n >> m) {
        long long ans = 1LL << 60;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= m && i < M; i++) dp[i] = 1;
        for (int mi = 1; mi < M; mi++) {
            if (n * mi > ans) break;
            long long l = 0, r = dp[mi] - 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                long long tmp_ans = 0;
                long long sum = 0;
                for (int i = mi; i <= mi + 3 && i < M && sum < n; i++) {
                    if (i == mi) {
                        tmp_ans += 1LL * i * min(n - sum, dp[mi] - mid);
                        sum += dp[mi] - mid;
                    } else {
                        if (i <= mi + m) {
                            tmp_ans += 1LL * i * min(n - sum, dp[i] + mid);
                            sum += dp[i] + mid;
                        } else {
                            tmp_ans += 1LL * i * min(n - sum, dp[i]);
                            sum += dp[i];
                        }
                    }
                }
                if (sum < n) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                    ans = min(ans, tmp_ans);
                }
            }
            for (int i = 1; i <= m && i + mi < M; i++) {
                dp[i + mi] += dp[mi];
            }
        }
        cout << ans << endl;
   }
    return 0;
}
