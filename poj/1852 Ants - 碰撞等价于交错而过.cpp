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

int L, n;
int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (cin >> L >> n) {
        int ans1 = 0, ans2 = 0;
        for (int i = 0, x; i < n; i++) {
            cin >> x;
            ans1 = max(ans1, min(x, L - x));
            ans2 = max(ans2, max(x, L - x));
        }
        cout << ans1 << " " << ans2 << endl;
    }
    return 0;
}
