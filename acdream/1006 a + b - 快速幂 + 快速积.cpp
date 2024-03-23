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
const int N = 1111;
const ll MOD = 10000000007LL;
int n;
ll a[N], k;

ll product_mod(ll a, ll b) {
    ll res = 0;
    while(b) {
        if(b & 1) res = (res + a) % MOD;
        a = (a + a) % MOD;
        b >>= 1;
    }
    return res;
}

ll power_mod(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res = product_mod(res, a);
        a = product_mod(a, a);
        b >>= 1;
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> n >> k;
        ll ans = 0, x;
        for(int i = 0; i < n; i++) {
            cin >> x;
            x = (x % MOD + MOD) % MOD;
            ans = (ans + power_mod(x, k)) % MOD;
        }
        cout << ans << endl;
    }
    return 0;
}
