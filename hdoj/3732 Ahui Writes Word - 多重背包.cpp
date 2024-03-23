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

const int N = 121;
const int M = 11111;
int dp[M], cnt[N];
char trash[20];
int n, m;
vector<pii> vec;
int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%s%d%d", trash, &a, &b);
            cnt[a * 11 + b]++;
        }
        vec.clear();
        for (int i = 0; i < 121; i++) {
            if (!cnt[i]) continue;
            int x = cnt[i], k = 0;
            int v = i / 11, c = i % 11;
            while (x + 1 > (1 << (k + 1))) k++;
            for (int j = 0; j < k; j++) {
                int a = 1 << j;
                vec.pb(mp(a * v, a * c));
            }
            int tmp = x + 1 - (1 << k);
            if (tmp > 0) {
                vec.pb(mp(tmp * v, tmp * c));
            }
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < vec.size(); i++) {
            for (int j = m; j >= vec[i].se; j--) {
                dp[j] = max(dp[j], dp[j - vec[i].se] + vec[i].fi);
            }
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}
