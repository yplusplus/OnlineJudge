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

const int N = 11111;
int a[N], n;
struct BIT {
    int c[N];
    void clear() { memset(c, 0, sizeof(c)); }
    void update(int l, int r, int v) {
        update(l, v);
        update(r + 1, -v);
    }
    void update(int x, int v) {
        for (int i = x; i < N; i += lowbit(i)) c[i] += v;
    }
    int query(int x) {
        if (x == 0) return 0;
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) res += c[i];
        return res;
    }
    int lowbit(int x) { return x & (-x); }
} bit;

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        bit.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            bit.update(i, i, a[i]);
        }
        int pos = 1;
        a[n + 1] = a[0] = 0;
        int ans = n;
        for (int i = 1; i <= n + 1; i++) {
            int pre = bit.query(i - 1);
            if (a[i] < pre) {
                int delta = pre - a[i];
                bit.update(pos, i - 1, -delta);
                while (bit.query(pos) < 0) pos++;
                ans = min(ans, i - pos);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
