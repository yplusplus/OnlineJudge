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
#define eps 1e-8
int m;
double s, p;
int dcmp(double x) {
    return (x < -eps) ? -1 : (x > eps);
}

int check(double x) {
    double ss = s;
    int i;
    for(i = 1; i <= m; i++) {
        if(dcmp(ss) <= 0) break;
        double a = ss * p;
        double b = x - a;
        ss -= b;
    }
    if(i < m) return -1;
    else return dcmp(ss);
}

int main() {
    while(cin >> s >> m >> p) {
        p /= 100.0;
        double l = 0.0, r = 1e15, mid;
        for(int i = 0; i < 100; i++) {
            mid = (l + r) / 2.0;
            int sign = check(mid);
            if(sign == 0) break;
            else if(sign == 1) l = mid;
            else r = mid;
        }
        printf("%.5f\n", mid);
    }
    return 0;
}
