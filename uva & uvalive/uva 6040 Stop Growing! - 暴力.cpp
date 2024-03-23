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
const int N = 5;
int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        printf("Case #%d: ", Case++);
        ll sum = 0, m;
        for (int i = 0, x; i < N; i++) {
            cin >> x;
            sum += x;
        }
        cin >> m;
        if (sum < m && sum <= 0) {
            puts("-1");
        } else {
            int ans = 0;
            while (1) {
                if (sum >= m) {
                    printf("%d\n", ans);
                    break;
                } else ans++, sum <<= 1;
            }
        }
    }
    return 0;
}
