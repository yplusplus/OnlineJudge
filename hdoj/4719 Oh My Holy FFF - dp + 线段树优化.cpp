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

struct SegmentTree {
    ll v[N * 3];
    void init(int n) {
        for (int i = 1; i <= n * 3; i++) v[i] = -linf;
    }
    void pushup(int p) {
        v[p] = max(v[p << 1], v[p << 1 | 1]);
    }
    void insert(int p, int l, int r, int x, ll val) {
        if (l == r) {
            v[p] = val;
            return;
        }
        int mid = l + r >> 1;
        if (x <= mid) insert(p << 1, l, mid, x, val);
        else insert(p << 1 | 1, mid + 1, r, x, val);
        pushup(p);
    }
    ll query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) return v[p];
        int mid = l + r >> 1;
        ll res = -linf;
        if (L <= mid) res = max(res, query(p << 1, l, mid, L, R));
        if (R > mid) res = max(res, query(p << 1 | 1, mid + 1, r, L, R));
        return res;
    }
} segmentTree;

pii person[N];
ll dp[N];
int n, L;
int main() {
    ios::sync_with_stdio(false);
    int T, Case = 1;
    cin >> T;
    //scanf("%d", &T);
    while (T--) {
        cin >> n >> L;
        //scanf("%d%d", &n, &l);
        segmentTree.init(n);
        for (int i = 1, h; i <= n; i++) {
            cin >> h;
            person[i] = mp(h, i);
        }
        sort(person + 1, person + 1 + n);
        queue<pii> que;
        for (int i = 1; i <= n; i++) {
            while (!que.empty() && person[i].fi > que.front().fi) {
                segmentTree.insert(1, 1, n, que.front().se, dp[que.front().se] - que.front().fi);
                que.pop();
            }
            int x = person[i].se;
            if (x <= L) dp[x] = 1LL * person[i].fi * person[i].fi;
            else dp[x] = -linf;
            ll ret = segmentTree.query(1, 1, n, max(x - L, 1), x);
            if (ret > -linf) {
                dp[x] = max(dp[x], ret + 1LL * person[i].fi * person[i].fi);
            }
            if (dp[x] > -linf) {
                que.push(person[i]);
            }
        }
        cout << "Case #" << Case++ << ": ";
        if (dp[n] == -linf) cout << "No solution" << endl;
        else cout << dp[n] << endl;
    }
    return 0;
}
