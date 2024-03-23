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
#define eps 1e-6
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 50050
pair<double, double> p[maxn];
int n;
double calc(double x) {
    double res = 0.0;
    for(int i = 0; i < n; i++) {
        double delta = abs(x - p[i].fi);
        res += p[i].se * delta * delta * delta;
    }
    return res;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        double a, b;
        for(int i = 0; i < n; i++) {
            scanf("%lf%lf", &a, &b);
            p[i] = mp(a, b);
        }
        double l = p[0].fi - eps, r = p[n-1].fi + eps;
        double ans = 1e300;
        while(l + eps < r) {
            double mid = l + (r - l) / 3.0;
            double mmid = r - (r - l) / 3.0;
            double tmp_mid = calc(mid);
            double tmp_mmid = calc(mmid);
            if(tmp_mid < tmp_mmid) {
                ans = tmp_mid;
                r = mmid;
            } else {
                ans = tmp_mmid;
                l = mid;
            }
        }
        printf("Case #%d: %.0f\n",Case++, ans);
    }
    return 0;
}
