#pragma comment(linker, "/STACK:102400000,102400000")
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
int pos[N], son[N];
int n, root, tot;
vector<int> vec[N];

void dfs(int u, int fa) {
    pos[u] = ++tot;
    son[u] = 1;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa) continue;
        dfs(v, u);
        son[u] += son[v];
    }
}

struct BIT {
    int c[N];
    void clear() { memset(c, 0, sizeof(c)); }
    void insert(int x, int v) {
        for (int i = x; i <= n; i += lowbit(i)) c[i] += v;
    }
    int query(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) res += c[i];
        return res;
    }
} bit;

int main() {
    while (~scanf("%d%d", &n, &root), n + root) {
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            vec[b].pb(a);
        }
        tot = 0;
        dfs(root, 0);
        bit.clear();
        for (int i = 1; i <= n; i++) {
            int l = pos[i], r = pos[i] + son[i] - 1;
            int res = bit.query(r) - bit.query(l);
            bit.insert(pos[i], 1);
            printf("%d%c", res, i == n ? '\n' : ' ');
        }
    }
    return 0;
}
