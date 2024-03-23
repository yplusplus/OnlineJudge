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
#define maxn 1000050
int n;
double x[maxn], y[maxn];
int main() {
    while(~scanf("%d", &n), n) {
        for(int i = 0; i < n; i++) {
            scanf("%lf%lf", &x[i], &y[i]);
        }
        sort(x, x + n);
        sort(y, y + n);
        printf("%.2f %.2f\n", x[n>>1], y[n>>1]);
    }
    return 0;
}
