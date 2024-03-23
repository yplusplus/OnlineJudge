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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 40;
const int K = 22;
int dp[N][K];
int digit[N];
int x, y, k, b;

int dfs(int i, int cnt, bool e) {
    if (cnt > k) return 0;
    if (i == -1) return cnt == k;
    if (!e && dp[i][cnt] != -1) return dp[i][cnt];
    int res = 0;
    int u = e ? digit[i] : (b - 1);
    for (int d = 0; d <= u && d <= 1; d++) {
        res += dfs(i - 1, (d == 1) + cnt, e & d == u);
    }
    return e ? res : dp[i][cnt] = res;
}

int calc(int x) {
    int tot = 0;
    while (x) {
        digit[tot++] = x % b;
        x /= b;
    }
    return dfs(tot - 1, 0, 1);
}

int main() {
    while (cin >> x >> y >> k >> b) {
        memset(dp, -1, sizeof(dp));
        int ans = calc(y) - calc(x - 1);
        cout << ans << endl;
    }
    return 0;
}
