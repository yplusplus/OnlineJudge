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
const double dinf = 1e100;
const ll linf = 1LL << 55;
const double eps = 1e-8;
const int N = 111111;
int n;
//nlognlogn
class Point {
    public:
    double x, y;
    void read() { scanf("%lf%lf", &x, &y); }
    double DistanceFrom(const Point &a) {
        return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
    }
} point[N], t[N];

bool cmpx(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool cmpy(const Point &a, const Point &b) {
    return a.y < b.y;
}

double ClosestPointDist(int l, int r) {
    if (l == r) return dinf;
    int mid = l + r >> 1;
    //cout << l << " " << r << " -> " << mid << endl;
    double d = min(ClosestPointDist(l, mid), ClosestPointDist(mid + 1, r));
    int tot = 0;
    for (int i = l; i <= r; i++) {
        if (fabs(point[mid].x - point[i].x) < d || fabs(point[mid].x - point[i].x) < eps) t[tot++] = point[i];
    }
    sort(t, t + tot, cmpy);
    for (int i = 0; i < tot; i++) {
        for (int j = i + 1; j < tot && j < i + 7; j++) {
            d = min(d, t[i].DistanceFrom(t[j]));
        }
    }
    return d;
}

int main() {
    while (~scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) point[i].read();
        sort(point, point + n, cmpx);
        printf("%.2f\n", ClosestPointDist(0, n - 1) * 0.5);
    }
    return 0;
}
