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
#define maxn 10050
int n;
double d, l, w;
double ans, good;
struct Person {
    double s, t;
    bool operator <(const Person &a) const {
        if(s != a.s) return s < a.s;
        return t < a.t;
    }
}p[maxn];

void solve() {
    sort(p + 1, p + n + 1);
    int tot = 1;
    for(int i = 2; i <= n; i++) {
        if(p[i].t < p[tot].t) p[++tot] = p[i];
    }
    double ans = 1e25;
    for(int i = 1; i <= tot; i++) {
        if(l * p[i].s > w) break;
        ans = min(ans, good + l * p[i].t);
        for(int j = i + 1; j <= tot; j++) {
            double ww = l * p[j].s;
            if(ww > w) ww = w;
            double y = (ww - l * p[i].s) / (p[j].s - p[i].s);
            ans = min(ans, good + y * p[j].t + (l - y) * p[i].t);
        }
    }
    if(ans > 1e24) printf("No solution\n");
    else printf("%.2f\n", ans);
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        good = 0.0;
        scanf("%d%lf%lf%lf", &n, &d, &l, &w);
        for(int i = 1; i <= n; i++) {
            scanf("%lf%lf", &p[i].s, &p[i].t);
            w -= p[i].s * d;
            good += p[i].t * d;
        }
        l -= d * n;
        if(w < 0 || l < 0) {
            printf("No solution\n");
            continue;
        }
        solve();
    }
    return 0;
}
