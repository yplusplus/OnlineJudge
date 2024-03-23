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
#define maxn 100050
int dp[maxn];
int eh[maxn], tot;
int F[maxn<<1], B[maxn<<1], pos[maxn];
int rmq[maxn<<1][16], rn;
int n, m;
struct Edge {
    int u, v, next;
}et[maxn<<1];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v) {
    Edge e = {u, v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}
void dfs(int u, int pre, int deep) {
    F[++rn] = u, B[rn] = deep, pos[u] = rn;
    for(int son = eh[u]; son != -1; son = et[son].next) {
        int v = et[son].v;
        if(v == pre) continue;
        dfs(v, u, deep + 1);
        dp[u] += dp[v];
        F[++rn] = u, B[rn] = deep;
    }
}
void Init_RMQ() {
    for(int i = 1; i <= rn; i++) rmq[i][0] = i;
    for(int j = 1; (1<<j) <= rn; j++) {
        for(int i = 1; i + (1<<j) - 1 <= rn; i++) {
            int a = rmq[i][j-1], b = rmq[i+(1<<(j-1))][j-1];
            if(B[a] < B[b]) rmq[i][j] = a;
            else rmq[i][j] = b;
        }
    }
}
int RMQ(int a, int b) {
    int k = int(log(1.0 + b - a) / log(2.0));
    int u = rmq[a][k], v = rmq[b-(1<<k)+1][k];
    if(B[u] < B[v]) return F[u];
    else return F[v];
}
int LCA(int a, int b) {
    a = pos[a], b = pos[b];
    if(a > b) return RMQ(b, a);
    else return RMQ(a, b);
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        init();
        int a, b;
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &a, &b);
            addedge(a, b), addedge(b, a);
        }
        memset(dp, 0, sizeof(dp));
        dfs(1, 0, 0);
        Init_RMQ();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &a, &b);
            dp[a]++, dp[b]++;
            dp[LCA(a, b)] -= 2;
        }
        rn = 0;
        dfs(1, 0, 0);
        int ans = 0;
        for(int i = 2; i <= n; i++) {
            if(dp[i] == 0) ans += m;
            else if(dp[i] == 1) ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
