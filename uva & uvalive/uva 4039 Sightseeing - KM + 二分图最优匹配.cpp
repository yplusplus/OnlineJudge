#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define MAX 110
#define maxn 110
int n, m;
const int inf = 100000000;
int g[MAX][MAX];

int d[MAX];
int maz[maxn][maxn], lx[maxn], ly[maxn], match[maxn], sy[maxn], slack[maxn], sx[maxn];
int nx, ny;
int q[maxn], tot;
bool dfs(int t) {
    sx[t] = 1;
    for (int i = 1; i <= ny; ++i) {
        if (sy[i])continue;
        if (maz[t][i] == lx[t] + ly[i]) {
            sy[i] = 1;
            if (match[i] == -1 || dfs(match[i])) {
                match[i] = t;
                return 1;
            }
        } else slack[i] = min(slack[i], lx[t] + ly[i] - maz[t][i]);
    }
    return 0;
}
void Change() {
    int Min = inf;
    for (int i = 1; i <= ny; ++i)
        if (!sy[i]) Min = min(Min, slack[i]);
    for (int i = 1; i <= nx; ++i)
        if (sx[i]) lx[i] -= Min;
    for (int i = 1; i <= ny; ++i) {
        if (sy[i]) ly[i] += Min;
        else slack[i] -= Min;
    }
}
int KM() {
    int ans = 0;
    memset(match, -1, sizeof (match));
    for (int i = 1; i <= nx; ++i) {
        for (int j = 1; j <= ny; ++j)
            slack[j] = inf;
        while (1) {
            memset(sy, 0, sizeof (sy));
            memset(sx, 0, sizeof (sx));
            if (dfs(i)) break;
            Change();
        }
    }
    for (int i = 1; i <= ny; ++i)
        if(match[i] != -1) ans += inf - maz[match[i]][i];
    return ans / 2;
}
void build() {
    memset(maz, 0, sizeof (maz));
    nx = tot;
    ny = tot;
    for(int i = 0; i < tot; i++)
        for(int j = 0; j < tot; j++) {
            if(i != j) maz[i+1][j+1] = inf - g[q[i]][q[j]];
        }
    memset(ly, 0, sizeof (ly));
    for (int i = 1; i <= nx; ++i) {
        lx[i] = -inf;
        for (int j = 1; j <= ny; ++j)
            lx[i] = max(lx[i], maz[i][j]);
    }
}

int floyd() {
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}

int main() {
    int T, x;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++)
                g[i][j] = inf;
            g[i][i] = 0;
        }
        int ans = 0;
        memset(d, 0, sizeof(d));
        for(int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            ans += w;
            g[u][v] = g[v][u] = w;
            d[u]++, d[v]++;
        }
        tot = 0;
        for(int i = 1; i <= n; i++)
            if(d[i] & 1) q[tot++] = i;
        floyd();
        build();
        int res = KM();
        cout << ans + res << endl;
        scanf("%d", &x);
        if(x == -1) break;
    }

    return 0;
}
