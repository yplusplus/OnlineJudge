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
#define maxn 110
#define maxm 210
int n, m, root;
int dp[maxn][maxm];
int val[maxn];
struct Edge {
    int v, w;
    Edge(){}
    Edge(int _v, int _w) {
        v = _v, w = _w;
    }
};
vector<Edge> vec[maxn];

void dfs(int u, int fa) {
    for(int i = 0; i <= m; i++) dp[u][i] = val[u];
    int size = vec[u].size();
    for(int i = 0; i < size; i++) {
        int v = vec[u][i].v, w = vec[u][i].w;
        if(v == fa) continue;
        dfs(v, u);
        for(int j = m; j; j--)
            for(int k = j - 2 * w; k >= 0; k--)
                dp[u][j] = max(dp[u][j], dp[u][j-2*w-k] + dp[v][k]);
    }
}

int main() {
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 1; i < n; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            vec[u].pb(Edge(v, w));
            vec[v].pb(Edge(u, w));
        }
        scanf("%d%d", &root, &m);
        dfs(root, -1);
        cout << dp[root][m] << endl;
    }
    return 0;
}
