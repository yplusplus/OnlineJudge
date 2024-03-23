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
#define maxn 2050
ll all;
ll resident[maxn], cnt[maxn];
ll dp[maxn][550];
ll up[maxn], down[maxn];
int son[maxn];
int n, k;
int eh[maxn], tot;
struct Edge {
    int v;
    ll w;
    int next;
}et[maxn<<1];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, ll w) {
    Edge e = {v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

inline ll MIN(ll a, ll b) {
    return a < b ? a : b;
}

void dfsForDown(int u, int fa) {
    cnt[u] = resident[u];
    son[u] = 1;
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        ll w = et[i].w;
        if(v == fa) continue;
        dfsForDown(v, u);
        son[u] += son[v];
        cnt[u] += cnt[v];
        down[u] += cnt[v] * w + down[v];
    }
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        ll w = et[i].w;
        if(v == fa) continue;
        for(int j = min(k, son[u]); j >= 1; j--) {
            dp[u][j] += down[v] + cnt[v] * w;
            for(int jj = 1; jj <= j - 1; jj++) {
                dp[u][j] = MIN(dp[u][j], dp[u][j-jj] + dp[v][jj]);
            }
        }
    }
}

void dfsForUp(int u, int fa, ll w) {
    if(fa != -1) up[u] = up[fa] + down[fa] - down[u] + (all - 2 * cnt[u]) * w;
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if(v == fa) continue;
        dfsForUp(v, u, et[i].w);
    }
}

int main() {
    int Case = 1;
    while(~scanf("%d%d", &n, &k)) {
        if(!n && !k) break;
        all = 0;
        init();
        for(int i = 1; i <= n; i++) {
            scanf("%d", &resident[i]);
            all += resident[i];
            down[i] = up[i] = 0;
            for(int j = 0; j <= k; j++)
                dp[i][j] = 0;
        }
        for(int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            addedge(a, b, c);
            addedge(b, a, c);
        }
        dfsForDown(1, -1);
        dfsForUp(1, -1, -1);
        ll ans = linf;
        for(int i = 1; i <= n; i++) {
            ans = MIN(ans, dp[i][k] + up[i]);
        }
        printf("Case %d: %lld\n", Case++, ans);
    }
    return 0;
}
