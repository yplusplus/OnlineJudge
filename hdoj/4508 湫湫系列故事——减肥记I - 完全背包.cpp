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

const int N = 111;
const int M = 111111;
int a[N], b[N];
int dp[M];
int n, m;
int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &a[i], &b[i]);
        }
        scanf("%d", &m);
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            for (int j = b[i]; j <= m; j++) {
                dp[j] = max(dp[j], dp[j - b[i]] + a[i]);
            }
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}
