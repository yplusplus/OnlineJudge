#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 111111;
const int MOD = 1000007;
int K, C, a[N], n;
void generater(int a[], int n, int K, int C) {
    for (int i = 1; i < n; i++) {
        a[i] = (1LL * K * a[i - 1] + C) % MOD;
    }
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &K, &C, &n, &a[0]);
        generater(a, n, K, C);
        sort(a, a + n);
        long long ans = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            ans += (1LL * i * a[i] - sum);
            sum += a[i];
        }
        printf("Case %d: %lld\n", Case++, ans);
    }
    return 0;
}
