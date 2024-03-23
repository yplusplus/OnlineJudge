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
#define maxn 10050
const int inf = 1 << 20;
vector<int> vec[maxn];
int n, dp[maxn][3];

void dfs(int u, int fa) {
    int size = vec[u].size();
    dp[u][0] = 1;
    dp[u][1] = inf;
    dp[u][2] = 0;
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dfs(v, u);
        dp[u][0] += min(dp[v][2], dp[v][0]);
        dp[u][2] += dp[v][1];
    }
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dp[u][1] = min(dp[u][1], dp[u][2] - dp[v][1] + dp[v][0]);
    }
}

int main() {
    int symbol = 0;
    while(symbol != -1) {
        scanf("%d", &n);
        for(int i = 0; i < maxn; i++) vec[i].clear();
        for(int i = 1, a, b; i < n; i++) {
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            vec[b].pb(a);
        }
        scanf("%d", &symbol);
        dfs(1, -1);
        cout << min(dp[1][0], dp[1][1]) << endl;
    }
    return 0;
}
