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
const int N = 111;
bool unlock[N];
int n;
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        memset(unlock, false, sizeof(unlock));
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                unlock[j] ^= 1;
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) ans += unlock[i];
        cout << ans << endl;
    }
    return 0;
}
