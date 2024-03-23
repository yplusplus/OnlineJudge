#pragma comment(linker, "/STACK:16777216")
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
ll ans;
ll son[N];
int n;
void dfs(int u, int fa) {
    son[u] = 1;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa) continue;
        dfs(v, u);
        son[u] += son[v];
        ans -= son[v] * son[v];
    }
    ll t = n - son[u];
    if (t) ans -= t * t;
    ans += 1LL * (n - 1) * (n - 1);
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            vec[b].pb(a);
        }
        ans = 0;
        dfs(1, 0);
        ans >>= 1;
        ans = 1LL * n * (n - 1) * (n - 2) / 6 - ans;
        cout << ans << endl;
    }
    return 0;
}
