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
const int N = 3333;
const int T = 11111;
int n, t;
pii p[N];
int dp[T];

bool cmp(const pii &a, const pii &b) {
    return a.fi * b.se < a.se * b.fi;
}

int main() {
    while (cin >> n >> t) {
        for (int i = 0; i < n; i++) {
            cin >> p[i].fi >> p[i].se;
        }
        sort(p, p + n, cmp);
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j + p[i].fi <= t; j++) {
                dp[j] = max(dp[j], dp[j + p[i].fi] + (j + p[i].fi) * p[i].se);
            }
        }
        cout << *max_element(dp, dp + t + 1) << endl;
    }
    return 0;
}
