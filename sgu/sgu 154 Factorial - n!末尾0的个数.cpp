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

ll q;

//求n!末尾有多少个0，由n!有多少5的因子决定。
//快速求n!因子5的个数

ll calc(ll x) {
    ll res = 0;
    while (x) {
        res += x / 5;
        x /= 5;
    }
    return res;
}

ll solve(ll q) {
    if (q == 0) return 1;
    ll l = 1, r = 1LL << 60;
    ll res = -1;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        ll tmp = calc(mid * 5);
        if (tmp == q) return mid * 5;
        else if (tmp < q) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int main() {
    while (cin >> q) {
        ll ans = solve(q);
        if (ans == -1) puts("No solution");
        else cout << ans << endl;
    }
    return 0;
}
