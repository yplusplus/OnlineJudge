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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 266666;
int n, k;
struct BIT {
    int c[N];
    inline int lowbit(int x) { return x & (-x); }
    void clear() { memset(c, 0, sizeof(int) * (n + 10)); }
    void update(int x) {
        for (int i = x; i <= n; i += lowbit(i)) c[i]++;
    }
    int query(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) res += c[i];
        return res;
    }
} bit;

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        ll ans = 0;
        bit.clear();
        for (int i = 0; i < k; i++) {
            int x;
            scanf("%d", &x);
            int l = 1, r = n;
            int pos = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                int t = mid - bit.query(mid);
                if (t >= x) {
                    pos = mid;
                    r = mid - 1;
                } else l = mid + 1;
            }
            bit.update(pos);
            ans += pos;
        }
        printf("Case %d: %I64d\n", Case++, ans);
    }
    return 0;
}
