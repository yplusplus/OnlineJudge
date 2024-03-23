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
const ll MOD = 365LL * 24 * 60 * 60;
pii sub[N];
int n;
bool cmp(const pii &a, const pii &b) {
    ll tmp1 = 1LL * a.fi * b.se;
    ll tmp2 = 1LL * a.se * b.fi;
    return tmp1 < tmp2;
}

int main() {
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &sub[i].fi, &sub[i].se);
        }
        sort(sub, sub + n, cmp);
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + ans * sub[i].se + sub[i].fi) % MOD;
        }
        cout << ans << endl;
    }
    return 0;
}
