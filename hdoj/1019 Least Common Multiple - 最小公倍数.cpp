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

ll __lcm(ll a, ll b) {
    ll gcd = __gcd(a, b);
    return a / gcd * b;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ll x;
            cin >> x;
            if (i == 0) ans = x;
            else {
                ans = __lcm(ans, x);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
