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

const int N = 1111;
vector<pii> vec[N];
int fa[N], q[N], s[N];
int dist[N][N];
int dp[N][N];
int n;
vector<int> anc[N];

void FindAncestor(int id, int u) {
    if (u == 0) return;
    anc[id].pb(u);
    FindAncestor(id, fa[u]);
}

void CalculateDistance(int id, int u, int w) {
    dist[u][id] = w;
    for (int i = 0; i < vec[u].size(); i++)
        CalculateDistance(id, vec[u][i].fi, w + vec[u][i].se);
}

void dfs(int u) {
    if (vec[u].size() == 0) {
        for (int i = 0; i < anc[u].size(); i++) {
            int ancestor = anc[u][i];
            if (dist[u][ancestor] > q[u]) dp[u][ancestor] = s[u];
            else dp[u][ancestor] = 0;
        }
        return;
    }
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].fi;
        dfs(v);
    }
    for (int i = 0; i < anc[u].size(); i++) {
        int ancestor = anc[u][i];
        int x = 0, y = 0;
        for (int j = 0; j < vec[u].size(); j++) {
            x += dp[vec[u][j].fi][ancestor];
            y += dp[vec[u][j].fi][u];
        }
        y += s[u];
        if (dist[u][ancestor] > q[u]) dp[u][ancestor] = y;
        else dp[u][ancestor] = min(x, y);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i <= n; i++) { vec[i].clear(); anc[i].clear(); }
        int root = -1;
        for (int i = 1; i <= n; i++) {
            int w;
            scanf("%d%d%d%d", &fa[i], &q[i], &s[i], &w);
            if (fa[i] == 0) root = i;
            vec[fa[i]].pb(mp(i, w));
        }
        for (int i = 1; i <= n; i++) {
            FindAncestor(i, i);
            anc[i].pb(i);
            CalculateDistance(i, i, 0);
        }
        dfs(root);
        printf("%d\n", dp[root][root]);
    }
    return 0;
}
