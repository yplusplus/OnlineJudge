#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "string"
#include "cctype"
#include "cmath"
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

ull x, y, z, k;
ull xpz, xz;
inline ull power(ull a, ull n) {
    ull res = 1;
    while(n) {
        if(n & 1) res = a * res;
        n >>= 1;
        a = a * a;
    }
    return res;
}

ull calc(ull l, ull r) {
    while(l <= r) {
        ull mid = (l + r) >> 1;
        ull res = xpz + power(mid, z) + xz * mid;
        if(res == k) return true;
        else if(res < k) l = mid + 1;
        else r = mid - 1;
    }
    return false;
}

int main() {
    while(cin >> k, k) {
        ull ans = 0;
        ull upperbound = (ull)ceil(sqrt(double(k)));
        for(z = 2; z <= 30LL; z++) {
            for(x = 1; x < upperbound; x++) {
                xpz = power(x, z);
                xz = x * z;
                if(xpz >= k || xz >= k) break;
                if(calc(x + 1, upperbound)) ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
