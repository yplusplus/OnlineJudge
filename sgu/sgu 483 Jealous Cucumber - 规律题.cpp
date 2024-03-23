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
ll n, h;
int main() {
    while(cin >> n >> h) {
        h++;
        ll mid = h * h;
        vector<ll> ans;
        ll step = 2 * h + 1;
        for(ll i = mid + h; i <= n; i += step, step += 2) {
            ans.pb(i);
        }
        reverse(ans.begin(), ans.end());
        ans.pb(mid);
        step = 2 * (h + 1);
        for(ll i = mid + 2 * h; i <= n; i += step, step += 2) {
            ans.pb(i);
        }
        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        puts("");
    }
    return 0;
}
