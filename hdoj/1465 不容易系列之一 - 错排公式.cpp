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

const int N = 21;
int n;
ll fac[N];
int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i-1] * i;
    while (~scanf("%d", &n)) {
        ll ans = 0;
        for (int i = 0; i <= n; i++) {
            if (i & 1) ans -= fac[n] / fac[i];
            else ans += fac[n] / fac[i];
        }
        cout << ans << endl;
    }
    return 0;
}
