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

ll dp[6][1<<4][2];
ll cnt[1<<4][1<<4][2];
int n;
void dfs(int i, int id, int mask, int nextMask, int cc) {
    if(i == 4) {
        cnt[id][nextMask][cc]++;
        return;
    }
    if(mask >> i & 1) {
        dfs(i + 1, id, mask, nextMask, cc);
    } else {
        dfs(i + 1, id, mask | (1 << i), nextMask, cc);
        dfs(i + 1, id, mask | (1 << i), nextMask | (1 << i), cc);
        if(i + 1 < 4 && (~mask >> i >> 1 & 1)) {
            dfs(i + 1, id, mask | (1 << i) | (1 << (i + 1)), nextMask, cc);
            if(cc == 0) {
                dfs(i + 1, id, mask | (1 << i) | (1 << (i + 1)), nextMask | (1 << i) | (1 << (i + 1)), 1);
            }
        }
    }
    return;
}

int main() {
    int all = 1 << 4;
    memset(cnt, 0, sizeof(cnt));
    for(int mask = 0; mask < all; mask++) {
       dfs(0, mask, mask, 0, 0); 
    }
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        memset(dp, 0, sizeof(dp));
        dp[1][0][0] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < all; j++) {
                for(int k = 0; k < all; k++) {
                    dp[i+1][k][1] += dp[i][j][0] * cnt[j][k][1];
                    dp[i+1][k][1] += dp[i][j][1] * cnt[j][k][0];
                    dp[i+1][k][0] += dp[i][j][0] * cnt[j][k][0];
                }
            }
        }
        cout << dp[n+1][0][1] << endl;
    }
    return 0;
}
