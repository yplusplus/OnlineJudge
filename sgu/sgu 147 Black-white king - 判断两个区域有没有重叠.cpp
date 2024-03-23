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

int n;
int wx, wy, bx, by, x, y;

//题意比较坑爹，实际上求两个区域有没有重叠部分
//注意，黑白王要走最短路，不能走锯齿形的路线

bool cross(int low1, int high1, int low2, int high2) {
    return !(high1 < low2 || high2 < low1);
}

bool inside(int y, int low, int high) {
    return low <= y && y <= high;
}

int work(int sx, int sy, int ex, int ey, int cnt) {
    int dir = (ex - sx) > 0 ? 1 : -1;
    for (int i = 1; i <= cnt; i++) {
        int low = 1, high = n;
        low = max(low, max(sy - i, ey - (abs(sx - ex) - i)));
        high = min(high, min(sy + i, ey + (abs(sx - ex) - i)));
        int xx = sx + dir * i;
        if ((abs(xx - x) == i && cross(low, high, y - i, y + i))
            || (abs(xx - x) < i && (inside(y - i, low, high) || inside(y + i, low, high)))) {
            return i;
        }
    }
    return inf;
}

int main() {
    while (cin >> n) {
        cin >> bx >> by;
        cin >> wx >> wy;
        cin >> x >> y;
        if (abs(bx - wx) < abs(by - wy)) {
            swap(bx, by);
            swap(wx, wy);
            swap(x, y);
        }
        int ans = inf;
        int cnt = (abs(wx - bx) - 2) >> 1;
        ans = min(ans, min(work(wx, wy, bx, by, cnt), work(bx, by, wx, wy, cnt)));
        if (ans == inf) {
            puts("NO");
            cout << abs(wx - bx) - 1 << endl;
        } else {
            puts("YES");
            cout << ans << endl;
        }
    }
    return 0;
}
