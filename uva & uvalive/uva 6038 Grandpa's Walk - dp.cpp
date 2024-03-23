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

const int N = 55;
int a[N][N];
int dp[N][N];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int n, m;
inline bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}
bool visit[N][N];
int dfs(int x, int y) {
    if (dp[x][y]) return dp[x][y];
    dp[x][y] = 0;
    for (int i = 0; i < 4; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if (!check(xx, yy) || a[xx][yy] >= a[x][y]) continue;
        visit[xx][yy] = false;
        dp[x][y] += dfs(xx, yy);
    }
    if (dp[x][y] == 0) dp[x][y] = 1;
    return dp[x][y];
}

int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        memset(dp, 0, sizeof(dp));
        memset(visit, true, sizeof(visit));
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dfs(i, j);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (visit[i][j]) {
                    ans += dfs(i, j);
                }
            }
        }
        printf("Case #%d: %d\n", Case++, ans);
    }
    return 0;
}
