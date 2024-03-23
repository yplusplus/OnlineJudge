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

ll power_mod(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % m;
        b >>= 1;
        a = (a * a) % m;
    }
    return res;
}

int main() {
    int n;
    while (~scanf("%d", &n)) {
        if (n == 0) break;
        int ans = (power_mod(2, n - 1, n) + 1) % n;
        printf("%d\n", ans);
    }
    return 0;
}
