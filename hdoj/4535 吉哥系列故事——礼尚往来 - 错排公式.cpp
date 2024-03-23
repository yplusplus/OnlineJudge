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
const int N = 111;
int n;
ll fac[N];
ll inv[N];
ll power_mod(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        b >>= 1;
        a = (a * a) % MOD;
    }
    return res;
}

ll mul(ll a, ll b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

ll add(ll a, ll b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = (fac[i-1] * i) % MOD;
    for (int i = 0; i < N; i++) {
        inv[i] = power_mod(fac[i], MOD - 2);
    }
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        ll ans = 0;
        for (int i = 0; i <= n; i++) {
            if (i & 1) ans = (((ans - mul(fac[n], inv[i])) % MOD) + MOD) % MOD;
            else ans = add(ans, mul(fac[n], inv[i]));
        }
        cout << ans << endl;
    }
    return 0;
}

