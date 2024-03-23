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
const int N = 30;
char maz[N][N];
int cnt[1 << 25];
int row[N];
int n, m;
int ans;

//暴力即可，时间复杂度O(2^25)

void dfs(int i, int count, int mask) {
    if (i == n) {
        ans = min(ans, max(count, cnt[mask]));
        return;
    }
    dfs(i + 1, count + 1, mask);
    dfs(i + 1, count, mask | row[i]);
}

int main() {
    cnt[0] = 0;
    for (int i = 1; i < 1 << 25; i++) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) {
            cin >> maz[i];
            row[i] = 0;
            for (int j = 0; j < m; j++) {
                if (maz[i][j] == '*') row[i] |= 1 << j;
            }
        }
        ans = 30;
        dfs(0, 0, 0);
        cout << ans << endl;
    }
    return 0;
}
