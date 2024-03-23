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

const int N = 222222;
struct SegmentTree {
    int lazy[N * 4];
    struct Node {
        ll sum;
        int val;
    } node[N * 4];
    void clear(int n) { memset(lazy, -1, sizeof(int) * (n + 10) * 4); }
    void pushup(int p) {
        node[p].sum = node[p << 1].sum + node[p << 1 | 1].sum;
        node[p].val = max(node[p << 1].val, node[p << 1 | 1].val);
    }
    void pushdown(int p, int l, int r) {
        if (lazy[p] != -1) {
            int mid = l + r >> 1;
            int t = lazy[p];
            lazy[p << 1] = lazy[p << 1 | 1] = t;
            node[p << 1].sum = 1LL * t * (mid + 1 - l);
            node[p << 1 | 1].sum = 1LL * t * (r - mid);
            node[p << 1].val = node[p << 1 | 1].val = t;
            lazy[p] = -1;
        }
    }
    void update(int p, int l, int r, int L, int R, int val) {
        if (L <= l && r <= R) {
            node[p].sum = 1LL * val * (r - l + 1);
            node[p].val = val;
            lazy[p] = val;
            return;
        }
        pushdown(p, l, r);
        int mid = l + r >> 1;
        if (L <= mid) update(p << 1, l, mid, L, R, val);
        if (R > mid) update(p << 1 | 1, mid + 1, r, L, R, val);
        pushup(p);
    }
    void update(int p, int l, int r, int pos, int val) {
        if (l == r) {
            node[p].sum = node[p].val = val;
            return;
        }
        pushdown(p, l, r);
        int mid = l + r >> 1;
        if (pos <= mid) update(p << 1, l, mid, pos, val);
        else update(p << 1 | 1, mid + 1, r, pos, val);
        pushup(p);
    }
    int query(int p, int l, int r, int val) {
        if (l == r) return l;
        pushdown(p, l, r);
        int mid = l + r >> 1;
        if (node[p << 1].val > val) return query(p << 1, l, mid, val);
        else return query(p << 1 | 1, mid + 1, r, val);
    }
} tree;

int n, a[N], b[N];
int nxt[N];
bool has[N];
int main() {
    while (~scanf("%d", &n), n) {
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
        sort(b + 1, b + 1 + n);
        int t = 0;
        if (b[1] != 0) t = 0;
        else {
            b[n + 1] = inf;
            for (int i = 1; i <= n; i++) {
                if (b[i] == b[i + 1]) continue;
                if (b[i] + 1 != b[i + 1]) {
                    t = b[i] + 1;
                    break;
                }
            }
        }
        set<int> numberSet;
        for (int i = 1; i <= n; i++) {
            has[i] = numberSet.count(a[i]) > 0;
            numberSet.insert(a[i]);
        }

        tree.clear(n);
        for (int i = n; i >= 1; i--) {
            tree.update(1, 1, n, i, t);
            if (a[i] < t && !has[i]) t = a[i];
        }

        map<int, int> pos;
        for (int i = n; i >= 1; i--) {
            if (pos.count(a[i]) == 0) {
                nxt[i] = n + 1;
            } else {
                nxt[i] = pos[a[i]];
            }
            pos[a[i]] = i;
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            //cout << tree.node[1].sum << endl;
            ans += tree.node[1].sum;
            if (tree.node[1].val > a[i]) {
                int ret = tree.query(1, 1, n, a[i]);
                if (ret < nxt[i]) {
                    tree.update(1, 1, n, ret, nxt[i] - 1, a[i]);
                }
            }
            tree.update(1, 1, n, i, 0);
        }
        cout << ans << endl;
    }
    return 0;
}
