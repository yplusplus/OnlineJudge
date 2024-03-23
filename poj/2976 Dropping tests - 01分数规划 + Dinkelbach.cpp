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
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define eps 1e-6
#define maxn 1050
int n, k;

struct Point {
    int a, b;
    double c;
    bool operator <(const Point &x) const {
        return c < x.c;
    }
}p[maxn];

double work(double l) {
    for(int i = 0; i < n; i++) p[i].c = 1.0 * p[i].a - l * p[i].b;
    sort(p, p + n);
    double sum = 0.0, suma = 0.0, sumb = 0.0;
    for(int i = k; i < n; i++) sum += p[i].c, suma += p[i].a, sumb += p[i].b;
    return suma / sumb;
}

void solve() {
    double ans = 0.0, tmp = 0.0;
    while(1) {
        tmp = work(ans);
        if(fabs(tmp - ans) < eps) break;
        ans = tmp;
    }
    printf("%d\n", (int)(100.0 * (tmp + 0.005)));
}

int main() {
    while(~scanf("%d%d", &n, &k)) {
        if(!n && !k) break;
        for(int i = 0; i < n; i++) scanf("%d", &p[i].a);
        for(int i = 0; i < n; i++) scanf("%d", &p[i].b);
        solve();
    }
    return 0;
}
