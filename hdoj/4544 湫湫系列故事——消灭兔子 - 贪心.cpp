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
int b[N];
pii p[N];
int n, m;
bool cmp(const pii &a, const pii &b) {
    return a.fi > b.fi;
}

void solve() {
    priority_queue<int, vector<int>, greater<int> > que;
    sort(b, b + n);
    reverse(b, b + n);
    sort(p, p + m, cmp);
    ll ans = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < m && p[j].fi >= b[i]) {
            que.push(p[j++].se);
        }
        if (que.empty()) {
            puts("No");
            return;
        } else {
            ans += que.top();
            que.pop();
        }
    }
    cout << ans << endl;
}

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &p[i].fi);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &p[i].se);
        }
        solve();
    }
    return 0;
}
