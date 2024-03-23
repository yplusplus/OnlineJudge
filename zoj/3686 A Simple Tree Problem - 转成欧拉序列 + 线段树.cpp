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
vector<int> vec[N];
int sum[N << 2];
int rev[N << 2];
pii p[N];
int n, m, tot;
void dfs(int u) {
    p[u].fi = ++tot;
    for (int i = 0; i < vec[u].size(); i++) {
        dfs(vec[u][i]);
    }
    p[u].se = tot;
}

void pushUp(int p) {
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}

void pushDown(int p, int l, int r) {
    if (rev[p]) {
        int mid = (l + r) >> 1;
        sum[p << 1] = mid - l + 1 - sum[p << 1];
        sum[p << 1 | 1] = r - mid - sum[p << 1 | 1];
        rev[p] = 0;
        rev[p << 1] ^= 1;
        rev[p << 1 | 1] ^= 1;
    }
}

void update(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        rev[p] ^= 1;
        sum[p] = r - l + 1 - sum[p];
        return;
    }
    pushDown(p, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(p << 1, l, mid, L, R);
    if (mid < R) update(p << 1 | 1, mid + 1, r, L, R);
    pushUp(p);
}

int query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return sum[p];
    }
    pushDown(p, l, r);
    int res = 0;
    int mid = (l + r) >> 1;
    if (L <= mid) res += query(p << 1, l, mid, L, R);
    if (mid < R) res += query(p << 1 | 1, mid + 1, r, L, R);
    pushUp(p);
    return res;
}

int main() {
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 2; i <= n; i++) {
            int fa;
            cin >> fa;
            vec[fa].pb(i);
        }
        tot = 0;
        dfs(1);
        memset(sum, 0, sizeof(sum));
        memset(rev, 0, sizeof(rev));
        while (m--) {
            char op[5];
            int x;
            scanf("%s%d", op, &x);
            if (op[0] == 'o') update(1, 1, n, p[x].fi, p[x].se);
            else cout << query(1, 1, n, p[x].fi, p[x].se) << endl;
        }
        puts("");
    }
    return 0;
}
