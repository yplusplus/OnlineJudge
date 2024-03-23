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
const double eps = 1e-12;
const ll linf = 1LL << 55;
const int N = 444;
double loc[N];
int n;
double y[N];

//很容易想到间隔太大或者太小都会导致答案很大
//应该是一个抛物线，于是可以三分这个间隔
//假设当前的间隔是dist，第一个点的新位置是x0
//那么xi = x0 + i * dist
//res = ∑| loc[i] - xi |
//    = ∑| loc[i] - x0 - i * dist |
//    = ∑| loc[i] - i * dist - x0 |
//    = ∑| y[i] - x0 | (y[i] = loc[i] - i * dist)
//那么现在等价有n个点，坐标分别是y[i]，求一个点x0，使得所有点到他的距离之和最小。
//好明显就是一个中位数定理，于是x0 = y[n / 2], y[]要先排序！！！

double calc(double dist) {
    double res = 0.0;
    for(int i = 0; i < n; i++) {
        y[i] = loc[i] - i * dist;
    }
    sort(y, y + n);
    double first = y[n >> 1];
    for(int i = 0; i < n; i++) {
        res += abs(y[i] - first);
    }
    return res;
}

int main() {
    while(cin >> n) {
        for(int i = 0; i < n; i++) {
            cin >> loc[i];
        }
        double l = 0.0, r = 1e30 + eps;
        for(int i = 0; i < 500; i++) {
            double mid = l + (r - l) / 3.0;
            double mmid = r - (r - l) / 3.0;
            double tmp_mid = calc(mid);
            double tmp_mmid = calc(mmid);
            if(tmp_mid < tmp_mmid) r = mmid;
            else l = mid;
        }
        printf("%.10f\n", calc(l) + eps);
        double first = y[n >> 1];
        for(int i = 0; i < n; i++) {
            printf("%.10f%c", first + i * l, i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
