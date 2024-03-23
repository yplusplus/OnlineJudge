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
const int N = 11;
const int M = 9;
int n, m;
int table[1<<M][1<<M];
ll dp[N][1<<M];

//dp
//按列状态压缩，先预处理行与行之间的情况
//转移很简单
//有个小优化，如果列数大于行数时，交换行列之后再计算

void dfs(int i, int id, int now, int next) {
    if (i == m) {
        if (now == (1 << m) - 1) table[id][next]++;
        return;
    }
    if (~now >> i & 1) {
        if (~next >> i & 1) {
            dfs(i + 1, id, now | (1 << i), next | (1 << i));
            if (i + 1 < m && (~now >> i >> 1 & 1)) {
                dfs(i + 1, id, now | (3 << i), next | (1 << i));
            }
            if (i + 1 < m && (~next >> i >> 1 & 1)) {
                dfs(i + 1, id, now | (1 << i), next | (3 << i));
            }
        }
        if (i + 1 < m && (~now >> i >> 1 & 1)) {
            dfs(i + 1, id, now | (3 << i), next);
            if (i + 1 < m && (~next >> i >> 1 & 1)) {
                dfs(i + 1, id, now | (3 << i), next | (1 << i << 1));
            }
        }
    }
    if (i + 1 < m && (~now >> i >> 1 & 1) && !(next & (3 << i))) {
        dfs(i + 1, id, now | (1 << i << 1), next | (3 << i));
    }
    dfs(i + 1, id, now, next);
}

int main() {
    while (cin >> n >> m) {
        if (n < m) swap(n, m);
        memset(table, 0, sizeof(table));
        int all = 1 << m;
        for (int mask = 0; mask < all; mask++) {
            dfs(0, mask, mask, 0);
        }
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int now = 0; now < all; now++) {
                if (dp[i][now] == 0) continue;
                for (int next = 0; next < all; next++) {
                    dp[i+1][next] += dp[i][now] * table[now][next];
                }
            }
        }
        cout << dp[n][0] << endl;
    }
    return 0;
}
