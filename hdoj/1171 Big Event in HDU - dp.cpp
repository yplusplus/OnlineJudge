#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int M = 66666;
int n;
bool dp[M];
int main() {
    while (cin >> n) {
        if (n < 0) break;
        memset(dp, false, sizeof(dp));
        dp[0] = true;
        int sum = 0;
        for (int i = 0, v, c; i < n; i++) {
            scanf("%d%d", &v, &c);
            sum += v * c;
            for (int j = 0; j < c; j++) {
                for (int k = M - 1; k >= v; k--) {
                    dp[k] |= dp[k-v];
                }
            }
        }
        for (int i = (sum + 1) / 2; i < M; i++) {
            if (dp[i]) {
                printf("%d %d\n", i, sum - i);
                break;
            }
        }
    }
    return 0;
}
