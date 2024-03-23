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
#define maxn 100050
int n;
pii p[maxn];
bool cmp(const pii &a, const pii &b) {
    int tmp1 = max(-a.se, a.fi - b.se);
    int tmp2 = max(-b.se, b.fi - a.se);
    return tmp1 < tmp2;
}
int main() {
    while(~scanf("%d", &n)) {
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &p[i].fi, &p[i].se);
        }
        sort(p, p + n, cmp);
        ll sum = 0, ans = 0;
        for(int i = 0; i < n; i++) {
            if(ans < sum - p[i].se) ans = sum - p[i].se;
            sum += p[i].fi;
        }
        cout << ans << endl;
    }
    return 0;
}
