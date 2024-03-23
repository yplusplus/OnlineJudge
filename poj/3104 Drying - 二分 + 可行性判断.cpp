#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 100050
int n;
ll val[maxn], ans, k;

bool check(ll t) {
    ll cnt = 0;
    for(int i = 0; i < n; i++) {
        if(val[i] > t) {
            cnt += (val[i] - t + k - 2) / (k - 1);
            if(cnt > t) return false;
        }
    }
    return true;
}

void solve() {
    ll l = 1, r = ans;
    while(l <= r) {
        ll mid = (l + r) >> 1;
        if(check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%lld\n", ans);
}

int main() {
    while(~scanf("%d", &n)) {
        ans = 0;
        for(int i = 0; i < n; i++) {
            scanf("%lld", &val[i]);
            ans = max(ans, val[i]);
        }
        scanf("%lld", &k);
        if(k == 1) printf("%lld\n", ans);
        else solve();
    }
    return 0;
}
