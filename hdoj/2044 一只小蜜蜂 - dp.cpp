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
const int N = 55;
ll dp[N];
int a, b;
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> a >> b;
        memset(dp, 0, sizeof(dp));
        dp[a] = 1;
        for (int i = a + 1; i <= b; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        cout << dp[b] << endl;
    }
    return 0;
}
