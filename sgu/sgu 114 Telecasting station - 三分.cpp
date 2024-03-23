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

const int N = 15555;
pair<double, double> city[N];
int n;

double calc(double x) {
    double res = 0;
    for(int i = 1; i <= n; i++) {
        res += abs(x - city[i].fi) * city[i].se;
    }
    return res;
}

int main() {
    while(cin >> n) {
        for(int i = 1; i <= n; i++) {
            cin >> city[i].fi >> city[i].se;
        }
        double l = 0.0, r = 55555.0;
        for(int i = 0; i < 100; i++) {
            double mid = (l + r) / 2.0;
            double mmid = (l + mid) / 2.0;
            double tmp_mid = calc(mid);
            double tmp_mmid = calc(mmid);
            if(tmp_mid > tmp_mmid) {
                r = mid;
            } else l = mmid;
        }
        printf("%.8f\n", (l + r) / 2.0);
    }
    return 0;
}
