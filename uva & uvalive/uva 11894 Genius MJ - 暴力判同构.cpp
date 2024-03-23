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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 100050
struct Point {
    int x, y;
    Point(){}
    Point(int _x, int _y) {
        x = _x, y = _y;
    }
    bool operator<(const Point &a) const {
        if(x != a.x) return x > a.x;
        else return y > a.y;
    }
    bool operator!=(const Point &a) const {
        return !(x == a.x && y == a.y);
    }
    Point operator-(const Point &a) const {
        Point c = Point(x - a.x, y - a.y);
        return c;
    }
}a[maxn], b[maxn], c[maxn];
int n;
bool check() {
    sort(c, c + n);
    Point d = a[0] - c[0];
    for(int i = 0; i < n; i++) {
        if(a[i] - c[i] != d) return false;
    }
    return true;
}
bool solve() {
    for(int i = 0; i < n; i++) {
        c[i] = b[i];
    }
    if(check()) return true;
    for(int i = 0; i < n; i++) {
        c[i] = Point(-b[i].y, b[i].x);
    }
    if(check()) return true;
    for(int i = 0; i < n; i++) {
        c[i] = Point(-b[i].x, -b[i].y);
    }
    if(check()) return true;
    for(int i = 0; i < n; i++) {
        c[i] = Point(b[i].y, -b[i].x);
    }
    if(check()) return true;
}
int main() 
{
    int T, x, y;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            a[i] = Point(x, y);
        }
        sort(a, a + n);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            b[i] = Point(x, y);
        }
        if(solve()) puts("MATCHED");
        else puts("NOT MATCHED");
    }
    return 0;
}
