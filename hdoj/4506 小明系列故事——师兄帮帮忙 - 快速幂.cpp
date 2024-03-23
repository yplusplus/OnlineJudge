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
const int N = 111111;
const ll MOD = 1000000007LL;
int n, t, k, a[N];

ll power_mod(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        b >>= 1;
        a = (a * a) % MOD;
    }
    return res;
}

void gao() {
    ll tmp = power_mod(k, t);
    for (int i = 1; i <= n; i++) {
        a[i] = (tmp * a[i]) % MOD;
    }
    t %= n;
    bool flag = false;
    for (int i = n - t + 1; i <= n; ++i) {
        if (flag) printf(" ");
        printf("%d", a[i]);
        flag = true;
    }
    for (int i = 1; i <= n - t; ++i) {
        if (flag) printf(" ");
        printf("%d", a[i]);
        flag = true;
    }
    puts("");
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d%d%d", &n, &t, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        gao();
    }
    return 0;
}
