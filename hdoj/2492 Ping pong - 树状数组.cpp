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
#define maxn 20050
#define MAX 100050
int n;
int a[maxn];
int val[MAX];
int le_min[maxn], le_max[maxn], ri_min[maxn], ri_max[maxn];
void update(int x, int v) {
    for(int i = x; i < MAX; i += lowbit(i))
        val[i] += v;
}

int sum(int x) {
    int res = 0;
    for(int i = x; i; i -= lowbit(i))
        res += val[i];
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        memset(val, 0, sizeof(val));
        for(int i = 1; i <= n; i++) {
            le_min[i] = sum(a[i]);
            le_max[i] = i - 1 - le_min[i];
            update(a[i], 1);
        }
        memset(val, 0, sizeof(val));
        for(int i = n; i; i--) {
            ri_min[i] = sum(a[i]);
            ri_max[i] = n - i - ri_min[i];
            update(a[i], 1);
        }
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += le_min[i] * ri_max[i] + le_max[i] * ri_min[i];
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
