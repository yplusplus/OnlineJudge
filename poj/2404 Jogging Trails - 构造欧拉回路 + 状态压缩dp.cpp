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
#define maxn 20
int maz[maxn][maxn];
int dp[1<<maxn];
int degree[maxn], n, m;
vector<pii> vec;

void floyd() {
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
}

int main() {
    while(~scanf("%d", &n)) {
        if(!n) break;
        scanf("%d", &m);
        memset(degree, 0, sizeof(degree));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                maz[i][j] = i == j ? 0 : inf;
        int ans = 0;
        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            a--, b--;
            ans += c;
            degree[a]++, degree[b]++;
            if(c < maz[a][b]) maz[a][b] = c;
            maz[b][a] = maz[a][b];
        }
        floyd();
        int Q[maxn], tot = 0;
        for(int i = 0; i < n; i++)
            if(degree[i] & 1) Q[tot++] = i;
        vec.clear();
        for(int i = 0; i < tot; i++) {
            for(int j = 0; j < i; j++) {
                vec.pb(mp((1 << i) | (1 << j), maz[Q[i]][Q[j]]));
            }
        }
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        for(int mask = 0; mask < (1 << tot); mask++) {
            if(dp[mask] == -1) continue;
            for(int i = 0; i < vec.size(); i++) {
                if((mask & vec[i].fi) == 0) {
                    int nextMask = mask|vec[i].fi;
                    if(dp[nextMask] == -1) dp[nextMask] = dp[mask] + vec[i].se;
                    else dp[mask|vec[i].fi] = min(dp[mask|vec[i].fi], dp[mask] + vec[i].se);
                }
            }
        }
        cout << ans + dp[(1 << tot) - 1] << endl;
    }
    return 0;
}
