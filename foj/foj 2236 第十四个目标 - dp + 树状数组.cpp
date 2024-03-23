#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MOD = 1000000007;
const int N = 100100;
int n;
int a[N];

int add(int a, int b) { return (a + b) % MOD; }

struct BIT {
    int c[N];
    inline int lowbit(int x) { return x & (-x); }
    void clear() { memset(c, 0, sizeof(c)); }
    void add(int x, int v) { for (int i = x; i <= n; i += lowbit(i)) c[i] = ::add(c[i], v); }
    int sum(int x) { int res = 0; for (int i = x; i > 0; i -= lowbit(i)) res = ::add(res, c[i]); return res; }
} bit;

int main() {
    while (~scanf("%d", &n)) {
        vector<int> vec(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            vec[i] = a[i];
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        bit.clear();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
            int t = add(bit.sum(x - 1), 1);
            ans = add(ans, t);
            bit.add(x, t);
        }
        printf("%d\n", ans);
    }
    return 0;
}
