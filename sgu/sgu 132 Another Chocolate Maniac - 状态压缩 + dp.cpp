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
const int N = 77;
const int M = 10;
int n, m;
int row[N];
char str[M];
int dp[2][1<<7][1<<7];
int st[55], tot;
struct Node {
    int now, next, cnt;
    Node(){}
    Node(int _now, int _next, int _cnt) {
        now = _now, next = _next, cnt = _cnt;
    }
};
vector<Node> table[1<<7];

//按行状态压缩，然后dp
//刚开始状态设少了，后面增加了一维
//因为无效状态很多，可以预处理出所有合法状态，或者用个队列维护有效状态
//要用滚动数组，否则会MLE
//dp部分只是一个很简单的转移

bool check(int mask) {
    for (int i = 0; i < m - 1; i++) {
        if (!(mask & (3 << i))) return false;
    }
    return true;
}

bool check2(int now, int next) {
    for (int i = 0; i < m; i++) {
        if (!(now & (1 << i)) && !(next & (1 << i))) return false;
    }
    return true;
}

void dfs(int i, int id, int now, int next, int cnt) {
    if (i == m) {
        if (check(now)) {
            table[id].pb(Node(now, next, cnt));
        }
        return;
    }
    if (~now >> i & 1) {
        dfs(i + 1, id, now | (1 << i), next | (1 << i), cnt + 1);
        if (i + 1 < m && (~now >> i >> 1 & 1)) {
            dfs(i + 2, id, now | (3 << i), next, cnt + 1);
        }
    }
    dfs(i + 1, id, now, next, cnt);
}

void update(int &x, int w) {
    if (x == -1) x = w;
    else x = min(x, w);
}

int main() {
    while (cin >> n >> m) {
        int all = 1 << m;
        tot = 0;
        for (int now = 0; now < all; now++) {
            if (check(now)) st[tot++] = now;
        }
        for (int i = 1; i <= n; i++) {
            cin >> str;
            row[i] = 0;
            for (int j = 0; j < m; j++) {
                if (str[j] == '*') {
                    row[i] |= 1 << j;
                }
            }
        }
        for (int now = 0; now < all; now++) {
            table[now].clear();
            dfs(0, now, now, 0, 0);
        }
        memset(dp, -1, sizeof(dp));
        dp[1][all-1][row[1]] = 0;
        row[n+1] = all - 1;
        for (int i = 1; i <= n; i++) {
            memset(dp[(i + 1) & 1], -1, sizeof(dp[0]));
            for (int j = 0; j < tot; j++) {
                for (int mask = 0; mask < all; mask++) {
                    if (dp[i & 1][st[j]][mask] == -1) continue;
                    for (int k = 0; k < table[mask].size(); k++) {
                        int now = table[mask][k].now;
                        int next = table[mask][k].next;
                        int cnt = table[mask][k].cnt;
                        if (next & row[i+1]) continue;
                        if (!check2(st[j], now)) continue;
                        update(dp[(i + 1) & 1][now][next | row[i+1]], dp[i & 1][st[j]][mask] + cnt);
                    }
                }
            }
        }
        int ans = inf;
        for (int j = 0; j < tot; j++) {
            if (dp[(n + 1) & 1][st[j]][row[n+1]] != -1) {
                ans = min(ans, dp[(n + 1) & 1][st[j]][row[n+1]]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
