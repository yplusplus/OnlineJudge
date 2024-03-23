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
unsigned dp[N][35][35];
int digit[N];

unsigned dfs(int i, int cnt, int ones, bool e) {
    if (cnt > ones) return 0;
    if (i == -1) return cnt == ones;
    if (!e && ~dp[i][cnt][ones]) return dp[i][cnt][ones];
    unsigned res = 0;
    int u = e ? digit[i] : 1;
    for (int d = 0; d <= u; d++) {
        res += dfs(i - 1, cnt + (d == 1), ones, e & d == u);
    }
    return e ? res : dp[i][cnt][ones] = res;
}

unsigned calc(unsigned x, int ones) {
    int tot = 0;
    while (x) {
        digit[tot++] = x & 1;
        x >>= 1;
    }
    return dfs(tot - 1, 0, ones, 1);
}

unsigned solve(int n, int m, int k) {
    unsigned a = n, b = m;
    for (int i = 1; i <= 31; i++) {
        unsigned t = calc(b, i) - (a == 0 ? 0 : calc(a - 1, i));
        if (k > t) k -= t;
        else {
            unsigned l = a, r = b, res = 0;
            while (l <= r) {
                unsigned mid = (r - l) / 2 + l;
                t = calc(mid, i) - (a == 0 ? 0 : calc(a - 1, i));
                if (t >= k) {
                    res = mid;
                    r = mid - 1;
                } else l = mid + 1;
            }
            return res;
        }
    }
}

int main() {
    memset(dp, -1, sizeof(dp));
    int n, m, k;
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        if (n == 0 || m == 0) k--;
        if (k == 0) puts("0");
        else printf("%d\n", solve(n, m, k));
    }
    return 0;
}
