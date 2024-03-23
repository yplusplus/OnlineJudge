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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 1000050
int n, c;
ll a[maxn], dp[maxn], D[maxn];
int que[maxn], le, ri;

int main() {
    while(~scanf("%d%d", &n, &c), n + c) {
        for(int i = 1; i <= n; i++) scanf("%I64d", &a[i]);
        le = ri = 0;
        D[0] = a[1] * a[1];
        que[ri++] = 0;
        for(int i = 1; i <= n; i++) {
            while(le + 1 < ri && (D[que[le+1]] - D[que[le]]) <= 2 * a[i] * (a[que[le+1]+1] - a[que[le]+1]))
                le++;
            int ft = que[le];
            dp[i] = dp[ft] + c + (a[i] - a[ft+1]) * (a[i] - a[ft+1]);
            D[i] = dp[i] + a[i+1] * a[i+1];
            while(le + 1 < ri && (D[que[ri-1]] - D[que[ri-2]]) * (a[i+1] - a[que[ri-1]+1]) >= (D[i] - D[que[ri-1]]) * (a[que[ri-1]+1] - a[que[ri-2]+1]))
                ri--;
            que[ri++] = i;
        }
        printf("%I64d\n", dp[n]);
    }
    return 0;
}
