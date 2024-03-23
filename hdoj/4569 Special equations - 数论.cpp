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

const int magic = 5;
int a[magic], b[magic];

ll pri, pp;
int deg;
int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &deg);
        for (int i = deg; i >= 0; i--) {
            scanf("%d", &a[i]);
        }
        cin >> pri;
        pp = pri * pri;
        for (int i = deg; i >= 0; i--) {
            a[i] = (a[i] % pp + pp) % pp;
        }
        ll ans = -1;
        for (ll i = 0; i < pri; i++) {
            ll sum = 0;
            ll tmp = 1;
            for (int j = 0; j <= deg; j++) {
                sum = (sum + tmp * a[j]) % pri;
                tmp = (tmp * i) % pri;
            }
            if (sum != 0) continue;
            ll x = i;
            while (x < pp) {
                sum = 0, tmp = 1;
                for (int j = 0; j <= deg; j++) {
                    sum = (sum + tmp * a[j]) % pp;
                    tmp = (tmp * x) % pp;
                }
                if (sum == 0) {
                    ans = x;
                    break;
                } else x += pri;
            }
            if (ans != -1) break;
        }
        printf("Case #%d: ", Case++);
        if (ans == -1) puts("No solution!");
        else cout << ans << endl;
    }
    return 0;
}
