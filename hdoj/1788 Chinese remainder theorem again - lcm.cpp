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

ll a;
int n;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);    
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

int main() {
    while (cin >> n >> a, n + a) {
        ll l = 1, m;
        for (int i = 0; i < n; i++) {
            cin >> m;
            l = lcm(l, m);
        }
        if (l - a <= 0) l += l - a;
        else l -= a;
        cout << l << endl;
    }
    return 0;
}
