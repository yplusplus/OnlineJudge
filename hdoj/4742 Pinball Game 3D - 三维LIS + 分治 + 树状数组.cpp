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

int getint() {
    int t = 0;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) {
        t = t * 10 + ch - '0';
        ch = getchar();
    }
    return t;
}

const int N = 111111;
struct Node {
    int x, y, z, id;
    void read(int _id) {
        x = getint(), y = getint(), z = getint();
        id = _id;
    }
} node[N], tmp[N];
int n;
pii dp[N];

const ll MOD = 1LL << 30;

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

void update(pii &now, const pii &a) {
    if (now.fi < a.fi) now = a;
    else if (now.fi == a.fi) now.se = (int) add(now.se, a.se);
}

struct BIT {
    pii c[N];
    int lowbit(int x) { return (x & (-x)); }
    void clear() { 
        for (int i = 1; i <= n; i++) c[i] = mp(0, 0);
    }
    void update(int x) {
        for (int i = x; i <= n; i += lowbit(i)) c[i] = mp(0, 0);
    }
    void update(int x, pii v) {
        for (int i = x; i <= n; i += lowbit(i)) ::update(c[i], v);
    }
    pii query(int x) {
        pii res = mp(0, 0);
        for (int i = x; i; i -= lowbit(i)) ::update(res, c[i]);
        return res;
    }
} bit;

bool cmpx(const Node &a, const Node &b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

bool cmpy(const Node &a, const Node &b) {
    if (a.y != b.y) return a.y < b.y;
    if (a.z != b.z) return a.z < b.z;
    return a.x < b.x;
}

void solve(int l, int r) {
    if (l >= r) { return; }
    int mid = l + r >> 1;
    solve(l, mid);
    for (int i = l; i <= r; i++) {
        tmp[i] = node[i];
        tmp[i].x = i;
    }
    sort(tmp + l, tmp + r + 1, cmpy);
    for (int i = l; i <= r; i++) {
        if (tmp[i].x <= mid) {
            bit.update(tmp[i].z, dp[tmp[i].id]);
        } else {
            pii ret = bit.query(tmp[i].z);
            ret.fi++;
            update(dp[tmp[i].id], ret);
        }
    }
    for (int i = l; i <= r; i++) {
        if (tmp[i].x <= mid) bit.update(tmp[i].z);
    }
    solve(mid + 1, r);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        vector<int> vec;
        vec.resize(n);
        for (int i = 0; i < n; i++) {
            node[i].read(i);
            vec[i] = node[i].z;
            dp[i] = mp(1, 1);
        }
        sort(node, node + n, cmpx);
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        for (int i = 0; i < n; i++) {
            node[i].z = lower_bound(vec.begin(), vec.end(), node[i].z) - vec.begin() + 1;
        }
        bit.clear();
        solve(0, n - 1);
        pii ans = mp(0, 0);
        for (int i = 0; i < n; i++) {
            update(ans, dp[i]);
        }
        printf("%d %d\n", ans.fi, ans.se);
    }
    return 0;
}
