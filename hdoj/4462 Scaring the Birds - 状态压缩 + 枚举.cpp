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
const int K = 10;
pii pos[K];
int R[K];
bool isCorn[N][N], isCover[N][N];
int n, k;
int cnt[1 << K];
bool check() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (isCorn[i][j] && !isCover[i][j]) return false;
        }
    }
    return true;
}

void cover(int x, int y, int r) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (abs(i - x) + abs(j - y) <= r) {
                isCover[i][j] = true;
            }
        }
    }
}

void gao() {
    int ans = 100;
    for (int i = 0; i < (1 << k); i++) {
        memset(isCover, false, sizeof(isCover));
        for (int j = 0; j < k; j++) {
            if (i >> j & 1) cover(pos[j].fi, pos[j].se, R[j]);
        }
        if (check()) {
            ans = min(ans, cnt[i]);
        }
    }
    if (ans == 100) ans = -1;
    cout << ans << endl;
}

int main() {
    cnt[0] = 0;
    for (int i = 1; i < (1 << 10); i++) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
    while (cin >> n) {
        if (!n) break;
        cin >> k;
        memset(isCorn, true, sizeof(isCorn));
        for (int i = 0; i < k; i++) {
            int x, y;
            cin >> x >> y;
            isCorn[x][y] = false;
            pos[i] = mp(x, y);
        }
        for (int i = 0; i < k; i++) {
            cin >> R[i];
        }
        gao();
    }
    return 0;
}
