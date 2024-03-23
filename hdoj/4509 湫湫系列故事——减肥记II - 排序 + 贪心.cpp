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

const int N = 555555;
pair<int, int> p[N];

int n, ans;
int main() {
    while (~scanf("%d", &n)) {
        ans = 24 * 60;
        int a, b, x, y;
        for (int i = 0; i < n; i++) {
            scanf("%d:%d %d:%d", &a, &b, &x, &y);
            p[i] = mp(a * 60 + b, x * 60 + y);
        }
        sort(p, p + n);
        int pp = 0;
        while (pp < n) {
            int nxt = pp, ri = p[pp].se;
            for (int i = pp + 1; i < n; i++) {
                if (p[i].fi < ri) {
                    nxt = i;
                    ri = max(ri, p[i].se);
                } else break;
            }
            ans -= (ri - p[pp].fi);
            pp = nxt + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
