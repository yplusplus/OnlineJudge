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
const ll MOD = 1000000007LL;

// c = b * x + a + x
// d = a * x + b

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll power_mod(ll a, ll n) {
    ll res = 1;
    a %= MOD;
    while (n) {
        if (n & 1) res = mul(res, a);
        n >>= 1;
        a = mul(a, a);
    }
    return res;
}

int main() {
    int q;
    while (cin >> q) {
        //ll a = 1, b = 1;
        //ll inv = power_mod(2, MOD - 2);
        ll a = 0, b = 0;
        while (q--) {
            char op[10];
            ll x;
            scanf("%s", op);
            cin >> x;
            /*
            if (op[0] == 'i') {
                a = mul(a, 1 + x);
                b = mul(b, MOD + 1 - x);
            } else if (op[0] == 'd') {
                a = mul(a, power_mod(1 + x, MOD - 2));
                b = mul(b, power_mod(MOD + 1 - x, MOD - 2));
            }
            ll ans = (a + MOD - b) % MOD;
            ans = mul(ans, inv);
            cout << ans << endl;
            */
            if (op[0] == 'i') {
                ll c = (mul(b, x) + x + a) % MOD;
                ll d = (mul(a, x) + b) % MOD;
                a = c, b = d;
            } else if (op[0] == 'd') {
                ll tmp;
                ll inv = power_mod(mul(x, x) + MOD - 1, MOD - 2);
                tmp = ((mul(b, x) + x - a) % MOD + MOD) % MOD;
                ll c = mul(tmp, inv);
                tmp = ((mul(a, x) - mul(x, x) - b) % MOD + MOD) % MOD;
                ll d = mul(tmp, inv);
                a = c, b = d;
            }
            cout << a << endl;
        }
    }
    return 0;
}
