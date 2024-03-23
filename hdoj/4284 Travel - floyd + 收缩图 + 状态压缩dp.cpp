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
const int inf = 1000000000;
const double dinf = 1e30;
const ll linf = 1LL << 55;
int dp[1<<16][16];
int chosen[16], gain[16], paid[16];
int n, m, initMoney, h;
int maz[110][110];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &initMoney);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) 
                maz[i][j] = (i == j) ? 0 : inf;

        for(int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u--, v--;
            maz[u][v] = min(maz[u][v], w);
            maz[v][u] = maz[u][v];
        }

        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);

        scanf("%d", &h);
        for(int i = 0; i < h; i++) {
            scanf("%d%d%d", &chosen[i], &gain[i], &paid[i]);
            chosen[i]--;
        }

        int nn = 1 << h;

        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < h; i++) {
            int res = initMoney - maz[0][chosen[i]] - paid[i];
            if(res >= 0) dp[1<<i][i] = res + gain[i];
        }

        for(int mask = 1; mask < nn; mask++) {
            for(int i = 0; i < h; i++) {
                if(dp[mask][i] < 0) continue;
                for(int j = 0; j < h; j++) {
                    if(~mask >> j & 1) {
                        int res = dp[mask][i] - maz[chosen[i]][chosen[j]] - paid[j];
                        if(res >= 0) dp[mask | (1 << j)][j] = max(dp[mask | (1 << j)][j], res + gain[j]);
                    }
                }
            }
        }

        bool isLegal = false;
        for(int i = 0; i < h; i++) {
            if(dp[nn-1][i] - maz[chosen[i]][0] >= 0) isLegal = true;
        }
        puts(isLegal ? "YES" : "NO");
    }
    return 0;
}
