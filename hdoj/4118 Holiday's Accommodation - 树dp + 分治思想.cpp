#pragma comment(linker, "/STACK:10006777216")
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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 100050
vector<pii> vec[maxn];
ll ans;
int n, son[maxn];
int dfs(int u, int fa) {
    int cnt = 1;
    for(int i = 0; i < vec[u].size(); i++) {
        if(vec[u][i].fi == fa) continue;
        int res = dfs(vec[u][i].fi, u);
        ans += 2LL * min(res, n - res) * vec[u][i].se;
        cnt += res;
    }
    return cnt;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            vec[a].pb(mp(b, c));
            vec[b].pb(mp(a, c));
        }
        ans = 0;
        dfs(1, -1);
        printf("Case #%d: %I64d\n", Case++, ans);
    }
    return 0;
}

