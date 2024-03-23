#pragma comment(linker,"/STACK:102400000,102400000");
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
const int inf = 1 << 25;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 1111111;
vector<int> vec[N];
int dp[N][3], n;

void checkmin(int &a, int b) {
    a = min(a, b);
}

void dfs(int u, int fa) {
    int t1 = inf, t2 = inf;
    int sum = 0, cnt = 0;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa) continue;
        dfs(v, u);
        cnt++;
        int t = min(dp[v][0], min(dp[v][1], dp[v][2]));
        sum += t;
        t = dp[v][1] - t;
        if (t < t1) t2 = t1, t1 = t;
        else if (t < t2) t2 = t;
    }
    if (cnt == 0) {
        memset(dp[u], 0, sizeof(dp[u]));
    } else {
        if (cnt >= 0) checkmin(dp[u][0], sum + 2 * cnt);
        if (cnt >= 1) checkmin(dp[u][1], sum + 2 * (cnt - 1) + t1);
        if (cnt >= 2) checkmin(dp[u][2], sum + 2 * (cnt - 2) + t1 + t2);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            vec[i].clear();
            for (int j = 0; j < 3; j++) dp[i][j] = inf;
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            vec[b].pb(a);
        }
        dfs(1, 0);
        int ans = inf;
        for (int i = 0; i < 3; i++) ans = min(ans, dp[1][i]);
        printf("%d\n", ans + 1);
    }
    return 0;
}
