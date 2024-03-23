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
#define lson p << 1, l, mid, L, R
#define rson p << 1 | 1, mid + 1, r, L, R
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 1000100;
const int magic = 5;
int n, m;
int a[N];

struct SegmentTree {
    int sum[N << 2], lazy[N << 2], id;
    SegmentTree() {}
    void pushUp(int p) {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
    }
    // 1 for and, 2 for or, 3 for xor;
    void pushDown(int p, int l, int r) {
        if (!lazy[p]) return;
        int mid = (l + r) >> 1;
        if (lazy[p] == 1) {
            sum[lc(p)] = sum[rc(p)] = 0;
            lazy[p << 1] = lazy[p << 1 | 1] = lazy[p];
        } else if (lazy[p] == 2) {
            sum[lc(p)] = mid - l + 1;
            sum[rc(p)] = r - mid;
            lazy[p << 1] = lazy[p << 1 | 1] = lazy[p];
        } else if (lazy[p] == 3) {
            sum[lc(p)] = mid - l + 1 - sum[lc(p)];
            sum[rc(p)] = r - mid - sum[rc(p)];
            lazy[lc(p)] = 3 - lazy[lc(p)];
            lazy[rc(p)] = 3 - lazy[rc(p)];
        }
        lazy[p] = 0;
    }
    void build(int p, int l, int r) {
        lazy[p] = 0;
        if (l == r) {
            sum[p] = a[l] >> id & 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushUp(p);
    }
    int query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return sum[p];
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        int res = 0;
        if (L <= mid) res += query(lson);
        if (R > mid) res += query(rson);
        pushUp(p);
        return res;
    }
    void update(int p, int l, int r, int L, int R, int opt) {
        if (L <= l && r <= R) {
            if (opt == 1) sum[p] = 0, lazy[p] = opt;
            else if (opt == 2) sum[p] = r - l + 1, lazy[p] = opt;
            else if (opt == 3) sum[p] = r - l + 1 - sum[p], lazy[p] = opt - lazy[p];
            return;
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) update(lson, opt);
        if (R > mid) update(rson, opt);
        pushUp(p);
    }
}T[magic];
int main() {
    int TT;
    cin >> TT;
    while (TT--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < magic; i++) {
            T[i].id = i;
            T[i].build(1, 0, n - 1);
        }
        char option[10];
        while (m--) {
            scanf("%s", option);
            int opt, l, r;
            if (option[0] == 'S') {
                scanf("%d%d", &l, &r);
                int ans = 0;
                for (int i = 0; i < magic; i++) {
                    ans += T[i].query(1, 0, n - 1, l, r) << i;
                }
                printf("%d\n", ans);
            } else {
                scanf("%d%d%d", &opt, &l, &r);
                if (option[0] == 'A') {
                    for (int i = 0; i < magic; i++) {
                        if (~opt >> i & 1) {
                            T[i].update(1, 0, n - 1, l, r, 1);
                        }
                    }
                } else if (option[0] == 'O') {
                    for (int i = 0; i < magic; i++) {
                        if (opt >> i & 1) {
                            T[i].update(1, 0, n - 1, l, r, 2);
                        }
                    }
                } else if (option[0] == 'X') {
                    for (int i = 0; i < magic; i++) {
                        if (opt >> i & 1) {
                            T[i].update(1, 0, n - 1, l, r, 3);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
