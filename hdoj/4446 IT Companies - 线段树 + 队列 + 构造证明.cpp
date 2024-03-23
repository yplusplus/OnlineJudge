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
#define lson p << 1, l, mid, L, R
#define rson p << 1 | 1, mid + 1, r, L, R
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111111;
int c[N];
int n;
int f[N << 2];
pii t[N << 2];

pii getMin(const pii &a, const pii &b) {
    if (a.fi < b.fi || (a.fi == b.fi && a.se < b.se)) return a;
    return b;
}

void pushup(int p) {
    t[p] = getMin(t[p << 1], t[p << 1 | 1]);
}

void pushdown(int p) {
    if (f[p]) {
        t[p << 1].fi -= f[p];
        t[p << 1 | 1].fi -= f[p];
        f[p << 1] += f[p];
        f[p << 1 | 1] += f[p];
        f[p] = 0;
    }
}

void build(int p, int l, int r) {
    f[p] = 0;
    if (l == r) {
        scanf("%d", &t[p].fi);
        t[p].se = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void modify(int p, int l, int r, int pos) {
    if (l == r && l == pos) {
        t[p].fi = inf;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(p << 1, l, mid, pos);
    else modify(p << 1 | 1, mid + 1, r, pos);
    pushup(p);
}

void modify(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        f[p]++;
        t[p].fi--;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (L <= mid) modify(lson);
    if (R > mid) modify(rson);
    pushup(p);
}


int ans[N << 1], tot;

int main() {
    while (scanf("%d", &n), n) {
        build(1, 1, n);
        queue<int> que;
        int company = 0, branch = 0;
        tot = 0;
        while (tot < (n << 1)) {
            pii res = mp(inf, -1);
            if (company < n) {
                res = t[1];
            }
            if (res.fi < 0) break;
            if (res.fi == 0) {
                ans[tot++] = res.se;
                if (res.se - 1 >= 1) modify(1, 1, n, 1, res.se - 1);
                modify(1, 1, n, res.se);
                que.push(res.se);
                company++;
            } else {
                if (que.empty()) break;
                ans[tot++] = -que.front();
                if (que.front() + 1 <= n) modify(1, 1, n, que.front() + 1, n);
                que.pop();
                branch++;
            }
        }
        if (tot == 2 * n) {
            for (int i = tot - 1; i >= 0; i--) {
                printf("%d ", ans[i]);
            }
            puts("");
        } else puts("Impossible");
    }
    return 0;
}
