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
const int inf = 1 << 30;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 15;
int a[N][N];
int cnt[N], tot;
int ans;
void dfs(int i, int pre, int tmp) {
    if (tmp >= ans) return;
    if (i == tot) {
        ans = min(ans, tmp);
        return;
    }
    for (int d = 0; d < 10; d++) {
        if (!cnt[d]) continue;
        if (i == 0 && d == 0) continue;
        cnt[d]--;
        dfs(i + 1, d, tmp + a[d][pre]);
        cnt[d]++;
    }
}

int main() {
    int T, x;
    cin >> T;
    while (T--) {
        cin >> x;
        memset(a, 0, sizeof(a));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        tot = 0;
        while (x) {
            tot++;
            cnt[x % 10]++;
            x /= 10;
        }
        ans = inf;
        dfs(0, 10, 0);
        cout << ans << endl;
    }
    return 0;
}
