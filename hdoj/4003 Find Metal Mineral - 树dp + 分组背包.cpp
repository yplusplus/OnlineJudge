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
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define pii pair<int, int>
#define mp make_pair
#define maxn 10050
#define maxm 1000050

int n, s, cnt;
int eh[maxn], tot;
int dp[maxn][15];
struct Edge {
    int u, v, w, next;
}et[maxm];

void addedge(int u, int v, int w) {
    Edge e = {u, v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void dfs(int u, int fa) {
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v, w = et[i].w;
        if(v == fa) continue;
        dfs(v, u);
        for(int j = cnt; j >= 0; j--) {
            dp[u][j] += dp[v][0] + 2 * w;
            for(int k = 1; k <= j; k++) {
                dp[u][j] = min(dp[u][j], dp[u][j-k] + dp[v][k] + k * w);
            }
        }
    }
}

int main() {
    int u, v, w;
    while(~scanf("%d%d%d", &n, &s, &cnt)) {
        init();
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < n - 1; i++) {
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w), addedge(v, u, w);
        }
        dfs(s, -1);
        printf("%d\n", dp[s][cnt]);
    }
    return 0;
}
