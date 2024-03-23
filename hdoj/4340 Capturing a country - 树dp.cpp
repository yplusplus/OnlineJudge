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
#define maxn 110
int n;
int a[maxn], b[maxn];
vector<int> vec[maxn];
int dp[maxn][2][2];

void dfs(int u, int fa) {
    int sumA = 0, sumB = 0;
    int deltaA = inf, deltaB = inf;
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dfs(v, u);
        sumA += min(dp[v][0][0], dp[v][1][1]);
        sumB += min(dp[v][0][1], dp[v][1][0]);
        deltaA = min(deltaA, dp[v][0][1] - min(dp[v][0][0], dp[v][1][1]));
        deltaB = min(deltaB, dp[v][1][1] - min(dp[v][0][1], dp[v][1][0]));
    }
    dp[u][0][0] = sumA + a[u] / 2;
    dp[u][0][1] = sumA + a[u] / 2 + min(deltaA, a[u] / 2 + a[u] % 2);
    dp[u][1][0] = sumB + b[u] / 2;
    dp[u][1][1] = sumB + b[u] / 2 + min(deltaB, b[u] / 2 + b[u] % 2);
}

int main() {
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            vec[u].pb(v);
            vec[v].pb(u);
        }
        dfs(1, -1);
        printf("%d\n", min(dp[1][0][1], dp[1][1][1]));
    }
    return 0;
}
