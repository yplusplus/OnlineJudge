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
#define maxn 1000050
int n;
pii tree[maxn<<2];
int dp[maxn], pre[maxn];
int a[maxn];

void pushup(int p) {
    tree[p] = max(tree[p<<1], tree[p<<1|1]);
}

pii query(int L, int R, int l, int r, int p) {
    if(L <= l && r <= R) {
        return tree[p];
    }
    int mid = (l + r) >> 1;
    pii res = mp(-1, -1);
    if(L <= mid) res = max(res, query(L, R, l, mid, p << 1));
    if(R > mid) res = max(res, query(L, R, mid + 1, r, p << 1 | 1));
    return res;
}

void update(int val, pii x, int l, int r, int p) {
    if(l == r) {
        tree[p] = max(tree[p], x);
        return;
    }
    int mid = (l + r) >> 1;
    if(val <= mid) update(val, x, l, mid, p << 1);
    else update(val, x, mid + 1, r, p << 1 | 1);
    pushup(p);
}

int main() {
    while(~scanf("%d", &n)) {
        for(int i = 1; i < (maxn << 2); i++) {
            tree[i].fi = 0, tree[i].se = -1;
        }
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        int ans = -1, idx = -1;
        for(int i = 1; i <= n; i++) {
            pii res = query(a[i], a[i], 0, maxn - 1, 1);
            if(a[i] - 2 >= 0) res = max(res, query(0, a[i] - 2, 0, maxn - 1, 1));
            res = max(res, query(a[i] + 2, maxn - 1, 0, maxn - 1, 1));
            dp[i] = res.fi + 1;
            pre[i] = res.se;
            update(a[i], mp(dp[i], i), 0, maxn - 1, 1);
            if(ans < dp[i]) {
                ans = dp[i];
                idx = i;
            }
        }
        cout << n - ans << endl;
        vector<int> vec;
        while(idx != -1) {
            vec.pb(a[idx]);
            idx = pre[idx];
        }
        for(int i = vec.size() - 1; i >= 0; i--) {
            printf("%d%c", vec[i], i ? ' ' : '\n');
        }
    }
    return 0;
}
