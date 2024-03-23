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
const int N = 222222;
int n, m, k;
int w[N], c[N], sumW[N], sumC[N];
int bs(int a, int x) {
    int l = 0, r = a;
    int res = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if((sumW[a] - sumW[mid]) * k >= x) {
            res = mid, l = mid + 1;
        } else r = mid - 1;
    }
    return res;
}

int main() {
    while(cin >> n >> m >> k) {
        sumW[0] = sumC[0] = 0;
        for(int i = 1; i <= n; i++) {
            cin >> w[i] >> c[i];
            sumW[i] = sumW[i-1] + w[i];
            sumC[i] = sumC[i-1] + c[i];
        }

        int l = 0, r = n;
        int ansMoney = 0;
        pii ans = mp(0, 0);
        for(int last = n; last - m >= 1; last--) {
            int res = bs(last - m, sumW[last] - sumW[last - m]);
            if(res == -1) break;
            int tmp = sumC[res] + sumC[n] - sumC[last];
            if(tmp > ansMoney) {
                ansMoney = tmp;
                ans = mp(res + n - last, res);
            }
        }
        cout << ans.fi << " " << ansMoney << endl;
        string ansStr = "";
        for(int i = 0; i < ans.fi - ans.se; i++) ansStr += 'H';
        for(int i = 0; i < ans.se; i++) ansStr += 'T';
        cout << ansStr << endl;
    }
    return 0;
}
