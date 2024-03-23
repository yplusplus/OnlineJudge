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
#include "cassert"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111111;
const int M = 510;
const int G = 10010;
int dp[M][G];
int eh[N], tot;
int cost[N], value[N];
int n, g;
bool leaf[N];
struct Edge {
    int v, next;
} et[N];

void init() {
    for (int i = 0; i <= n; i++) eh[i] = -1;
    tot = 0;
}

void addedge(int u, int v) {
    Edge e = {v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void dfs(int u, int g) {
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (g < cost[v]) continue;
        if (!leaf[v]) {
            for (int j = 0; j <= g - cost[v]; j++) dp[v][j] = dp[u][j];
            dfs(v, g - cost[v]);
            for (int j = cost[v]; j <= g; j++) {
                dp[u][j] = max(dp[u][j], dp[v][j - cost[v]] + value[v]);
            }
        } else {
            for (int j = g; j >= cost[v]; j--) {
                dp[u][j] = max(dp[u][j], dp[u][j - cost[v]] + value[v]);
            }
        }
    }
}

int main() {
    while (~scanf("%d%d", &n, &g)) {
        init();
        for (int i = 0; i <= n; i++) { leaf[i] = true; }
        for (int i = 1; i <= n; i++) {
            int fa;
            scanf("%d%d%d", &cost[i], &value[i], &fa);
            assert(cost[i] >= 0);
            assert(value[i] >= 0);
            assert(fa >= 0);
            if (fa == i) fa = 0;
            addedge(fa, i);
            leaf[fa] = false;
        }
        for (int i = 0; i <= g; i++) dp[0][i] = 0;
        dfs(0, g);
        printf("%d\n", dp[0][g]);
    }
    return 0;
}
