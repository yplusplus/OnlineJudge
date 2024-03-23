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

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll power_mod(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

char str[111111];
int main() {
    while (~scanf("%s", &str)) {
        int len = strlen(str);
        ll m = MOD - 1;
        ll t = 0;
        for (int i = 0; i < len; i++) {
            t = (t * 10 + str[i] - '0') % m;
        }
        t = (t - 1 + m) % m;
        cout << power_mod(2, t) << endl;
    }
    return 0;
}
