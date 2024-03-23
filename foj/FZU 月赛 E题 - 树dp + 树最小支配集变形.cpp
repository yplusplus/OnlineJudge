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
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 50050
#define maxm 500500
const ll inf = 1LL << 60;
ll val[maxn], dp[maxn][3];
int n;
int eh[maxn], tot;
struct Edge {
    int v, next;
}et[maxm];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v) {
    Edge e = {v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void dfs(int u, int fa) {
    dp[u][0] = val[u];
    dp[u][1] = inf;
    dp[u][2] = 0;
    bool isleaf = true;
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if(v == fa) continue;
        dfs(v, u);
        isleaf = false;
        dp[u][0] += min(dp[v][0], dp[v][2]);
        dp[u][2] += min(dp[v][0], dp[v][1]);
    }
    if(!isleaf) {
        for(int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            if(v == fa) continue;
            dp[u][1] = min(dp[u][1], dp[u][2] - min(dp[v][0], dp[v][1]) + dp[v][0]);
        }
    }
}

int main() {
    int T, u, v, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        init();
        for(int i = 1; i <= n; i++) {
            scanf("%I64d", &val[i]);
        }
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v);
            addedge(u, v), addedge(v, u);
        }
        dfs(1, -1);
        printf("Case %d: %I64d\n", Case++, min(dp[1][0], dp[1][1]));
    }
    return 0;
}
