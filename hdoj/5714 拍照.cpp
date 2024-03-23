#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 11111;
int x[N], y[N], z[N], d[N];
int A[N << 1], B[N << 1];
int mx[N << 1];
int n;

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        vector<int> vec;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &x[i], &y[i], &z[i], &d[i]);
            vec.push_back(x[i] + z[i]);
            vec.push_back(y[i] - z[i]);
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        for (int i = 0; i < n; i++) {
            int L = y[i] - z[i];
            int R = x[i] + z[i];
            if (L > R) continue;
            L = lower_bound(vec.begin(), vec.end(), L) - vec.begin() + 1;
            R = lower_bound(vec.begin(), vec.end(), R) - vec.begin() + 1;
            if (d[i] == 1) {
                A[L]++, A[R + 1]--;
            } else {
                B[L - 1]--, B[R]++;
            }
        }
        int m = vec.size();
        mx[0] = 0;
        int sum = 0;
        for (int i = 1; i <= m; i++) {
             sum += A[i];
             mx[i] = max(mx[i - 1], sum);
        }
        sum = 0;
        int ans = 0;
        for (int i = m; i >= 1; i--) {
            sum += B[i];
            ans = max(ans, sum + mx[i]);
        }
        printf("Case #%d:\n%d\n", Case++, ans);
    }
    return 0;
}
