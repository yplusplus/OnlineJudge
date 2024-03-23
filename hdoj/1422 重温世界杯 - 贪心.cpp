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

const int N = 111111 << 1;
int a[N], b[N];
int n;
int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &a[i], &b[i]);
            a[i + n] = a[i];
            b[i + n] = b[i];
        }
        int money = 0;
        int ans = 0;
        int cnt = 0;
        for (int i = 0; i < (n << 1); i++) {
            if (money + a[i] - b[i] >= 0) {
                cnt++;
                money += a[i] - b[i];
            } else {
                cnt = money = 0;
            }
            ans = max(ans, min(cnt, n));
        }
        cout << ans << endl;
    }
    return 0;
}
