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
#define maxn 22
int p[maxn][4], r[maxn];
int cost[maxn];
int dp[1<<22];
int n, initPower;
int f[15];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &initPower);
        vector<pii> vec1, vec2;
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &p[i][3], &p[i][2], &p[i][1], &r[i]);
            f[0] = 0;
            for(int j = 1; j < 10; j++) {
                f[j] = inf;
                for(int k = 1; k <= 3 && k <= j; k++) {
                    f[j] = min(f[j], f[j - k] + p[i][k]);
                }
            }
            cost[i] = *min_element(f + 7, f + 10);
            if(cost[i] <= r[i]) vec1.pb(mp(cost[i], r[i]));
            else vec2.pb(mp(r[i], cost[i]));
        }
        
        /*
        memset(dp, -1, sizeof(dp));
        dp[0] = initPower;
        for(int mask = 0; mask < (n << 1) - 1; mask++) {
            if(dp[mask] == -1) continue;
            for(int i = 0; i < n; i++) {
                if(~mask >> i & 1) {
                    if(dp[mask] <= cost[i]) continue;
                    int nextMask = mask | (1 << i);
                    dp[nextMask] = max(dp[nextMask], dp[mask] - cost[i] + r[i]);
                }
            }
        }
        int ans = dp[(n << 1) - 1];
        if(ans == -1) puts("no");
        else printf("%d\n", ans);
        */
        //greedy algorithm
        sort(vec1.begin(), vec1.end());
        sort(vec2.begin(), vec2.end(), greater<pii>());
        int ansPower = initPower;
        for(int i = 0; i < vec1.size(); i++) {
            ansPower -= vec1[i].fi;
            if(ansPower <= 0) break;
            ansPower += vec1[i].se;
        }
        for(int i = 0; i < vec2.size(); i++) {
            ansPower -= vec2[i].se;
            if(ansPower <= 0) break;
            ansPower += vec2[i].fi;
        }
        if(ansPower > 0) printf("%d\n", ansPower);
        else puts("no");
    }
    return 0;
}
