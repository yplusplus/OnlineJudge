#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
double r, m;
int y;
int main() {
    while(~scanf("%lf%lf%d", &r, &m, &y)) {
        r = r / 100 + 1.0;
        int ans = (int)(pow(r, y) * m);
        printf("%d\n", ans);
    }
    return 0;
}
