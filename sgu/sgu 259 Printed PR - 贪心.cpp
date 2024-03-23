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
int n;
pii p[N];
//贪心
//对于两项任务a，b
//先a后b : max(a.T + a.L, a.T + b.T + b.L)
//先b后a : max(b.T + b.L, b.T + a.T + a.T)
//让值小的先执行不会更差
//一开始脑残居然把a.T和b.T约掉了！！！！！！！！！
bool cmp(const pii &a, const pii &b) {
    return max(a.fi + a.se, a.fi + b.fi + b.se) < max(b.fi + b.se, b.fi + a.fi + a.se);
}

int main() {
    while(cin >> n) {
        for(int i = 0; i < n; i++) {
            cin >> p[i].fi;
        }
        for(int i = 0; i < n; i++) {
            cin >> p[i].se;
        }
        int ans = 0;
        int curTime = 0;
        sort(p, p + n, cmp);
        for(int i = 0; i < n; i++) {
            curTime += p[i].fi;
            ans = max(ans, curTime + p[i].se);
        }
        cout << ans << endl;
    }
    return 0;
}
