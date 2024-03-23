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


const int N = 22222;
int a[N], b[N], c[N];
int n;
int check(ll mid) {
    ll cnt = 0;
    for (int i = 0; i < n; i++) {
        if (mid >= a[i]) {
            if (mid >= b[i]) {
                cnt += 1 + (b[i] - a[i]) / c[i];
            } else {
                cnt += 1 + (mid - a[i]) / c[i];
            }
        }
    }
    return cnt & 1;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    while (cin >> n) {
        for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i];
        ll l = 0, r = 1LL << 31;
        ll pos = -1;
        while (l <= r) {
            ll mid = l + r >> 1;
            if (check(mid)) pos = mid, r = mid - 1;
            else l = mid + 1;
        }
        if (pos == -1) {
            cout << "DC Qiang is unhappy." << endl;
        } else {
            ll cnt = 0;
            for (int i = 0; i < n; i++) {
                if (pos <= b[i] && pos >= a[i]) {
                    cnt += ((pos - a[i]) % c[i] == 0);
                }
            }
            cout << pos << " " << cnt << endl;
        }
    }
    return 0;
}
