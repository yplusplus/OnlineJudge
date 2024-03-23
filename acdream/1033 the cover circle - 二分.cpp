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
const double eps = 1e-12;
double w, h;

double getdist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool check(double radius) {
    if (radius * 2 > eps + w) return false;
    if (radius * 2 > eps + h) return false;
    double distance = getdist(radius, radius, w - radius, h - radius);
    if (radius * 2 > distance + eps) return false;
    return true;
}

int main() {
    while (~scanf("%lf%lf", &w, &h)) {
        double l = 0.0, r = min(w, h);
        for (int i = 0; i < 1000; i++) {
            double mid = (l + r) / 2.0;
            if (check(mid)) l = mid;
            else r = mid;
        }
        printf("%.3f\n", (l + r) / 2.0);
    }
    return 0;
}
