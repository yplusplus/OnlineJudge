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
ll n;
void update(ll &ansr, ll &ansk, ll tmpr, ll tmpk) {
    if(tmpk == -1) return;
    if(ansr * ansk > tmpr * tmpk) {
        ansr = tmpr, ansk = tmpk;
    } else if(ansr * ansk == tmpr * tmpk && ansr > tmpr) {
        ansr = tmpr, ansk = tmpk;
    }
}

ll calc(ll r, ll k) {
    ll tmp = 1, res = 0;
    for(ll i = 0; i <= r; i++) {
        res += tmp;
        tmp *= k;
    }
    return res;
}

ll bsearch(ll r, ll x) {
    ll le = 1, ri = (ll)ceil(pow(x, 1.0 / r));
    while(le <= ri) {
        ll mid = (le + ri) >> 1;
        ll tmp = calc(r, mid);
        if(tmp == x) {
            return mid;
        } else if(tmp > x) {
            ri = mid - 1;
        } else {
            le = mid + 1;
        }
    }
    return -1;
}

int main() {
    while(cin >> n) {
        ll ansr = 1, ansk = n - 1;
        for(ll r = 2; r <= 40; r++) {
            update(ansr, ansk, r, bsearch(r, n));
            update(ansr, ansk, r, bsearch(r, n + 1));
        }
        cout << ansr << " " << ansk << endl;
    }
    return 0;
}
