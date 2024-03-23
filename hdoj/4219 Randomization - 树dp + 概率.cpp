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
#define maxn 70
#define maxs 530
int n, l, s;
double dp[maxn][maxs];
double son[maxs], tmp[maxs];
double e;
vector<int> vec[maxn];
void dfs(int u, int fa) {
    memset(dp[u], 0, sizeof(dp[u]));
    dp[u][0] = 1.0;
    int size = vec[u].size();
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dfs(v, u);
        memset(son, 0, sizeof(son));
        memset(tmp, 0, sizeof(tmp));
        for(int j = 0; j <= l; j++)
            for(int k = 0; k <= s; k++)
                if(j + k <= s)
                    son[j+k] += e * dp[v][k];
        for(int j = 0; j <= s; j++)
            for(int k = 0; k <= s - j; k++)
                tmp[max(j, k)] += son[j] * dp[u][k];
        for(int j = 0; j <= s; j++)
            dp[u][j] = tmp[j];
    }
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &l, &s);
        for(int i = 0; i <= n; i++) vec[i].clear();
        e = 1.0 / (1.0 + l);
        for(int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            vec[b].pb(a);
        }
        dfs(1, -1);
        double ans = 0.0;
        for(int i = 0; i <= s; i++) ans += dp[1][i];
        printf("Case %d: %.6f\n", Case++, ans);
    }
    return 0;
}
