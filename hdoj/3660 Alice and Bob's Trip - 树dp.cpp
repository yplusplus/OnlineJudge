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
#define maxm 600000 
#define maxn 505000

int n, L, R;
int tot, eh[maxn];
int dp[maxn];

struct Edge {
    int v, w, next;
}et[maxm];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int w) {
    Edge e = {v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void dfs(int u, int L, int R, int flag) {
    dp[u] = 0;
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v, w = et[i].w;
        dfs(v, L - w, R - w, !flag);
        if(dp[v] + w >= L && dp[v] + w <= R) {
            if(dp[u] == 0) dp[u] = dp[v] + w;
            else {
                if(flag) dp[u] = max(dp[u], dp[v] + w);
                else dp[u] = min(dp[u], dp[v] + w);
            }
        }
    }
}

int main() {
    int u, v, w;
    while(~scanf("%d%d%d", &n, &L, &R)) {
        init();
        for(int i = 1; i < n; i++) {
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
        }
        dfs(0, L, R, 1);
        if(R < L || dp[0] < L || dp[0] > R) printf("Oh, my god!\n");
        else printf("%d\n", dp[0]);
    }
    return 0;
}
