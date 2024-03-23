#include <iostream>
#include <cstring>
#include <climits>
#include <string>
using namespace std;

const int N = 15;
int D[N], C[N];
int sum[1 << N];
int dp[1 << N];
int pre[1 << N];
int n;
string subject[N];

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> subject[i] >> D[i] >> C[i];
        }
        int M = 1 << n;
        for (int i = 0; i < M; i++) {
            sum[i] = 0;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) 
                    sum[i] += C[j];
            }
        }
        memset(pre, -1, sizeof(pre));
        dp[0] = 0;
        for (int i = 1; i < M; i++) {
            dp[i] = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    int t = sum[(M - 1) ^ i] + C[j];
                    int tmp = dp[i ^ (1 << j)];
                    if (t > D[j])
                        tmp += t - D[j];
                    if (tmp < dp[i] || (tmp == dp[i] && name[pre[i]] > name[j])) {
                        dp[i] = tmp;
                        pre[i] = j;
                    }
                }
            }
        }
        cout << dp[M - 1] << endl;
        int x = M - 1;
        while (pre[x] != -1) {
            cout << subject[pre[x]] << endl;
            x ^= 1 << pre[x];
        }
    }
    return 0;
}
