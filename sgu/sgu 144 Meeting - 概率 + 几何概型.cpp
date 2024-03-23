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

double x, y, z;
int main() {
    while(cin >> x >> y >> z) {
        x *= 60;
        y *= 60;
        double tmp = y - (x + z);
        if(tmp < 0) tmp = 0;
        double ans = 1.0 - (tmp * tmp) / (y - x) / (y - x);
        printf("%.7f\n", ans);
    }
    return 0;
}
