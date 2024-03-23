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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const ll mod = 100000007LL;
#define maxn 10050
ll dp[maxn];
pii p[2010];
bool visit[2010];
int n, m, k;
void init() {
    dp[1] = 1, dp[2] = 1;
    for(int i = 3; i < maxn; i++)
        dp[i] = (i + 1) / 2 + dp[i-2];
}

bool check(int a, int b) {
    int x = p[a].fi, y = p[a].se;
    int xx = p[b].fi, yy = p[b].se;
    if(xx == x && (yy == y || yy == n - y + 1)) return true;
    if(xx == y && (yy == x || yy == n - x + 1)) return true;
    if(xx == n - y + 1 && (yy == x || yy == n - x + 1)) return true;
    if(xx == n - x + 1 && (yy == y || yy == n - y + 1)) return true;
    return false;
}

ll power_mod(ll a, ll n) {
    ll res = 1;
    while(n) {
        if(n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    init();
    while(~scanf("%d%d%d", &n, &m, &k)) {
        memset(visit, true, sizeof(visit));
        for(int i = 0; i < m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            x++, y++;
            p[i] = mp(x, y);
            for(int j = 0; j < i; j++) {
                if(visit[j] && check(i, j)) visit[j] = false;
            }
        }
        int cnt = 0;
        for(int i = 0; i < m; i++)
            if(visit[i]) cnt++;
        ll ans = power_mod(k, dp[n] - cnt);
        cout << ans << endl;
    }
    return 0;
}
