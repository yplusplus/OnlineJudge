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

const int N = 222;

int dp[N][1 << 8];
int f[1 << 8];
int p[N], s[N];
int n, m;
pii info[N];
bool visit[N][1 << 8];
vector<int> vec;
vector<pii> g[N];
queue<int> que;
int ans, anscost;

void update(int a, int b, int c) {
    if (dp[a][b] > c) {
        dp[a][b] = c;
        if (!visit[a][b]) {
            que.push(a);
            que.push(b);
            visit[a][b] = true;
        }
    }
}

bool check(int mask) {
    int cnt = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (mask >> i & 1) {
            cnt += info[vec[i]].fi;
        }
    }
    return cnt >= 0;
}

void solve() {
    while (!que.empty()) que.pop();
    int all = (1 << vec.size()) - 1;
    fill(dp[0], dp[n], inf);
    memset(visit, false, sizeof(visit));
    for (int i = 0; i < n; i++) {
        if (info[i].se) {
            que.push(i);
            que.push(info[i].se);
            dp[i][info[i].se] = 0;
            visit[i][info[i].se] = 1;
        }
    }
    int u, mask;
    while (!que.empty()) {
        u = que.front(), que.pop();
        mask = que.front(), que.pop();
        visit[u][mask] = false;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].fi, w = g[u][i].se;
            update(v, mask | info[v].se, dp[u][mask] + w);
        }
        int s = all ^ mask;
        for (int t = s; t; t = (t - 1) & s) {
            update(u, mask | t, dp[u][mask] + dp[u][t]);
        }
    }
    fill(&f[0], &f[1 << 8], inf);
    f[0] = 0;

    for (mask = 1; mask <= all; mask++) {
        if (check(mask)) {
            for (int i = 0; i < n; i++) {
                f[mask] = min(f[mask], dp[i][mask]);
            }
        }
        if (f[mask] == inf) continue;
        int s = all ^ mask;
        for (int t = s; t; t = (t - 1) & s) {
            f[mask | t] = min(f[mask | t], f[mask] + f[t]);
        }
    }

    ans = 0, anscost = 0;
    for (mask = 0; mask <= all; mask++) {
        if (f[mask] == inf) continue;
        int cnt = 0;
        for (int i = 0; i < vec.size(); i++) {
            if ((mask >> i & 1) && info[vec[i]].fi < 0) {
                cnt++;
            }
        }
        if (ans < cnt || (ans == cnt && anscost > f[mask])) {
            ans = cnt;
            anscost = f[mask];
        }
    }
}

int main() {
    while (cin >> n) {
        int cnt = 0;
        vec.clear();
        for (int i = 0; i < n; i++) {
            g[i].clear();
            info[i] = mp(0, 0);
            cin >> p[i] >> s[i];
            if (p[i] && s[i]) p[i]--, s[i]--, cnt++;
            if (p[i]) {
                info[i] = mp(p[i], 1 << vec.size());
                vec.pb(i);
            }
            if (s[i]) {
                info[i] = mp(-1, 1 << vec.size());
                vec.pb(i);
            }
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            a--, b--;
            g[a].pb(mp(b, c));
            g[b].pb(mp(a, c));
        }
        solve();
        cout << ans + cnt << " " << anscost << endl;
    }
    return 0;
}
