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
#define maxn 300050
ll val[maxn];
vector<pii> vec[maxn];
pair<ll, ll> rec[maxn];
int n;
ll ans;
bool cmp(const pii &a, const pii &b) {
    return a.se < b.se;
}

void dfs(int u, int fa, int color) {
    pair<ll, ll> tmp1 = mp(1, 0);
    pair<ll, ll> tmp2 = mp(0, 0);
    int curColor, nextColor;
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].fi;
        if(v == fa) continue;
        curColor = vec[u][i].se;
        if(i + 1 < vec[u].size()) {
            if(vec[u][i+1].fi != fa) nextColor = vec[u][i+1].se;
            else {
                if(i + 2 < vec[u].size()) nextColor = vec[u][i+2].se;
                else nextColor = 2;
            }
        } else nextColor = -2;
        dfs(v, u, curColor);
        ans += rec[v].fi * tmp1.se;
        ans += tmp1.fi * rec[v].se;
        ans += rec[v].fi * tmp1.fi * val[u];
        if(nextColor == curColor) {
            tmp2.fi += rec[v].fi, tmp2.se += rec[v].se;
        } else {
            tmp1.fi += tmp2.fi + rec[v].fi, tmp1.se += tmp2.se + rec[v].se;
            tmp2 = mp(0, 0);
        }
    }
    rec[u] = mp(0, 0);
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].fi;
        if(v == fa || vec[u][i].se == color) continue;
        rec[u].fi += rec[v].fi;
        rec[u].se += rec[v].se;
    }
    rec[u].fi += 1, rec[u].se += rec[u].fi * val[u];
}

int main() {
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; i++) {
            scanf("%I64d", &val[i]);
            vec[i].clear();
        }
        for(int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            vec[a].pb(mp(b, c));
            vec[b].pb(mp(a, c));
        }
        for(int i = 1; i <= n; i++) {
            sort(vec[i].begin(), vec[i].end(), cmp);
        }
        ans = 0;
        dfs(1, -1, -1);
        cout << ans << endl;
    }
    return 0;
}
