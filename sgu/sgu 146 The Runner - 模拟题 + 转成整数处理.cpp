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
const double eps = 1e-6;
int n;
double L;
ll v, t;
//水题，用double精度不够，乘个数变成整数直接处理
inline ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    while(cin >> L >> n) {
        ll len = (ll)round(L * 100000);
        ll sum = 0;
        for(int i = 0; i < n; i++) {
            cin >> v >> t;
            sum += v * t * 100000;
            sum %= len;
        }
        printf("%.4f\n", min(sum, len - sum) / 100000.0);
    }
    return 0;
}
