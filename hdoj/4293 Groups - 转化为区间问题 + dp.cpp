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
int n;
pii p[550];
int cnt[550][550], dp[550];
bool cmp(const pii &a, const pii &b) {
    return a.se < b.se;
}
int main() {
    while(~scanf("%d", &n)) {
        int tot = 0;
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if(a + b >= n) continue;
            a++, b = n - b;
            if(cnt[a][b]) cnt[a][b]++;
            else p[tot++] = mp(a, b), cnt[a][b]++;
        }
        sort(p, p + tot, cmp);
        for(int i = 0; i < tot; i++) {
            dp[i] = min(p[i].se - p[i].fi + 1, cnt[p[i].fi][p[i].se]);
            int rec = 0;
            for(int j = 0; j < i; j++) {
                if(p[j].se < p[i].fi)
                    rec = max(rec, dp[j]);
            }
            dp[i] += rec;
        }
        int ans = *max_element(dp, dp + tot);
        cout << ans << endl;
    }
    return 0;
}
