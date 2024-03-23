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

const int N = 888;
int n, a[N];
int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        ll ans = n * (n - 1) * (n - 2) / 6;
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            ll cnt = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) cnt += __gcd(a[i], a[j]) == 1;
            }
            sum += cnt * (n - 1 - cnt);
        }
        ans -= sum / 2;
        cout << ans << endl;
    }
    return 0;
}
