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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111111;
struct SegmentTree {
    int color[N << 2];
    void clear() { memset(color, 0, sizeof(color)); }
    void pushdown(int p) {
        if (color[p]) {
            color[p << 1] = color[p << 1 | 1] = color[p];
            color[p] = 0;
        }
    }
    void update(int p, int l, int r, int L, int R, int c) {
        if (L <= l && r <= R) { color[p] = c; return; }
        pushdown(p);
        int mid = l + r >> 1;
        if (L <= mid) update(p << 1, l, mid, L, R, c);
        if (mid < R) update(p << 1 | 1, mid + 1, r, L, R, c);
    }
    int query(int p, int l, int r, int pos) {
        if (l == r) return color[p];
        pushdown(p);
        int mid = l + r >> 1;
        if (pos <= mid) return query(p << 1, l, mid, pos);
        else return query(p << 1 | 1, mid + 1, r, pos);
    }
} T;

int next[N][2];
pii robot[N];
ll dp[N][2];
int n, s, m;
int main() {
    while (~scanf("%d%d%d", &n, &s, &m)) {
        T.clear();
        for (int i = 1; i <= m; i++) { scanf("%d%d", &robot[i].first, &robot[i].second); }
        memset(next, 0, sizeof(next));
        for (int i = m; i >= 1; i--) {
            if (robot[i].fi > 1) next[i][0] = T.query(1, 1, n, robot[i].fi - 1);
            if (robot[i].se < n) next[i][1] = T.query(1, 1, n, robot[i].se + 1);
            T.update(1, 1, n, robot[i].fi, robot[i].se, i);
        }
        for (int i = 0; i <= m; i++) { dp[i][0] = dp[i][1] = linf; }
        ll ans = linf;
        int nxt = T.query(1, 1, n, s);
        if (nxt == 0) ans = 0;
        else {
            if (robot[nxt].fi > 1) dp[nxt][0] = abs(s - robot[nxt].fi + 1);
            if (robot[nxt].se < n) dp[nxt][1] = abs(s - robot[nxt].se - 1);
        }
        for (int i = 1; i <= m && ans; i++) {
            if (next[i][0] == 0) ans = min(ans, dp[i][0]);
            if (next[i][1] == 0) ans = min(ans, dp[i][1]);
            if (next[i][0]) {
                int nxt = next[i][0];
                if (robot[nxt].fi > 1) dp[nxt][0] = min(dp[nxt][0], dp[i][0] + abs(robot[i].fi - robot[nxt].fi));
                if (robot[nxt].se < n) dp[nxt][1] = min(dp[nxt][1], dp[i][0] + abs(robot[i].fi - 2 - robot[nxt].se));
            }
            if (next[i][1]) {
                int nxt = next[i][1];
                if (robot[nxt].fi > 1) dp[nxt][0] = min(dp[nxt][0], dp[i][1] + abs(robot[i].se + 2 - robot[nxt].fi));
                if (robot[nxt].se < n) dp[nxt][1] = min(dp[nxt][1], dp[i][1] + abs(robot[i].se - robot[nxt].se));
            }
        }
        cout << ans << endl;
    }
    return 0;
}
