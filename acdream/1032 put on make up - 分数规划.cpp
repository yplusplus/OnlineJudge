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
const int N = 11111;
const double eps = 1e-8;
double a[N], b[N];

int n, k;

bool check(double mid) {
    double c[N];
    for (int i = 0; i < n; i++) {
        c[i] = a[i] - mid * b[i];
    }
    sort(c, c + n);
    reverse(c, c + n);
    double sum = 0.0;
    for (int i = 0; i < k; i++) {
        sum += c[i];
    }
    return sum > eps;
}

int main() {
    while (cin >> n >> k) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i] = log(a[i]);
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            b[i] = log(b[i]);
        }
        double l = 0, r = 55555;
        for (int i = 0; i < 50; i++) {
            double mid = (l + r) / 2.0;
            if (check(mid)) l = mid;
            else r = mid;
        }
        printf("%.3f\n", (l + r) / 2.0);
    }
    return 0;
}
