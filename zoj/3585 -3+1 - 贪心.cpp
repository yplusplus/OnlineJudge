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
#define maxn 20050
int n, a;
int cnt[5];
int main() {
    while(~scanf("%d", &n)) {
        ll ans = 0, res = 0;
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; i++) {
            scanf("%d", &a);
            cnt[a%3]++;
            ans += a / 3;
            res += a / 3;
        }
        if(res >= 1) ans += cnt[2], cnt[0] += cnt[2], cnt[2] = 0;
        while(res >= 2 && cnt[1]) {
            if(res >= cnt[1] * 2) {
                ans += cnt[1], res -= cnt[1], cnt[1] = 0;
            } else {
                ans += res / 2, cnt[1] -= res / 2, res -= res / 2;
            }
        }
        while(res >= 3) {
            ans += res / 3;
            res = res % 3 + res / 3;
        }
        cout << ans << endl;
    }
    return 0;
}
