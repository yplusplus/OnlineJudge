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
const int N = 111;
char s[N], t[N];
int dp[N][N][30];

int dfs(int l, int r, int c) {
    if (l > r) return 0;
    if (l == r) {
        if (c == 26) return s[l] != t[l];
        return c != t[l] - 'a';
    }
    if (dp[l][r][c] != -1) return dp[l][r][c];
    int res = inf;
    for (int i = l; i <= r; i++) {
        if (t[l] == t[i]) {
            if (c == 26) {
                if (s[l] == t[l] && s[i] == t[i]) res = min(res, dfs(l + 1, i - 1, c) + dfs(i + 1, r, c));
                else res = min(res, dfs(l + 1, i - 1, t[l] - 'a') + 1 + dfs(i + 1, r, c));
            } else {
                if (c == t[l] - 'a') res = min(res, dfs(l + 1, i - 1, c) + dfs(i + 1, r, c));
                else res = min(res, dfs(l + 1, i - 1, t[l] - 'a') + 1 + dfs(i + 1, r, c));
            }
        }
    }
    return dp[l][r][c] = res;
}

int main() {
    while (~scanf("%s%s", s, t)) {
        memset(dp, -1, sizeof(dp));
        cout << dfs(0, strlen(s) - 1, 26) << endl;
    }
    return 0;
}
