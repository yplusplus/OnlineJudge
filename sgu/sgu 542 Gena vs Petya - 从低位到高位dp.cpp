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

const int N = 222222;
ll a[N], a0[N], a1[N];
ll ways[N], nways[N];
int n;

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        ll xorSum = 0;
        ll min_ai = *min_element(a, a + n);
        for (int i = 0; i < n; i++) {
            xorSum ^= a[i] - min_ai;
        }
        memset(ways, 0, sizeof(ways));
        ways[0] = 1;
        while (*max_element(a, a + n) > 0) {
            int a0sz = 0, a1sz = 0;
            for (int i = 0; i < n; i++) {
                if (a[i] & 1) a1[a1sz++] = a[i];
                else a0[a0sz++] = a[i];
            }
            memset(nways, 0, sizeof(nways));
            int now0 = 0, now1 = 0;
            for (int i = 0; i <= n; i++) {
                int ones = a1sz - now1 + now0;
                //bit == 0
                if (ones % 2 == 0) {
                    nways[now0] += ways[i];
                }
                //bit == 1
                ones = n - ones;
                if (ones % 2 == 0) {
                    nways[a0sz + now1] += ways[i];
                }
                if (i < n) {
                    if (a[i] == 0) break;
                    if (a[i] & 1) now1++;
                    else now0++;
                }
            }
            memcpy(ways, nways, sizeof(ways));
            int sz = 0;
            for (int i = 0; i < a0sz; i++) {
                a[sz++] = a0[i] >> 1;
            }
            for (int i = 0; i < a1sz; i++) {
                a[sz++] = a1[i] >> 1;
            }
        }
        ll ans = ways[0];
        if (xorSum == 0) ans--;
        printf("%lld\n", ans);
    }
    return 0;
}
