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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111111;
int n;
double a[N], b[N], rate[N];
int rank[N];
double ans, profit[N];
int que[N], head, tail;
pair<double, double> f[N], tmp[N];

bool cmp(int i, int j) {
    return a[i] * b[j] < a[j] * b[i];
}

bool check(int i, int j, int k) {
    double res1 = (f[i].se - f[j].se) * (f[j].fi - f[k].fi);
    double res2 = (f[j].se - f[k].se) * (f[i].fi - f[j].fi);
    return res2 - res1 >= 0;
}

double calc(int i, int j) {
    return f[i].fi * a[j] + f[i].se * b[j];
}

void solve(int l, int r) {
    if (l == r) {
        ans = max(ans, profit[l]);
        f[l].se = ans / (a[l] * rate[l] + b[l]);
        f[l].fi = f[l].se * rate[l];
        return;
    }
    int mid = (l + r) >> 1;

    memcpy(que + l, rank + l, sizeof(int) * (r - l + 1));
    int p = l, q = mid + 1;
    for (int i = l; i <= r; i++) {
        if (que[i] <= mid) rank[p++] = que[i];
        else rank[q++] = que[i];
    }

    solve(l, mid);

    head = tail = 0;
    for (int i = l; i <= mid; i++) {
        while (tail >= 2 && check(que[tail - 2], que[tail - 1], i)) tail--;
        que[tail++] = i;
    }

    for (int i = mid + 1; i <= r; i++) {
        int now = rank[i];
        while (tail - head >= 2 && calc(que[head], now) < calc(que[head + 1], now)) head++;
        profit[now] = max(profit[now], calc(que[head], now));
    }

    solve(mid + 1, r);

    merge(f + l, f + mid + 1, f + mid + 1, f + r + 1, tmp + l);
    memcpy(f + l, tmp + l, sizeof(pair<double, double>) * (r - l + 1));
}

int main() {
    while (~scanf("%d%lf", &n, &ans)) {
        for (int i = 1; i <= n; i++) {
            scanf("%lf%lf%lf", &a[i], &b[i], &rate[i]);
            rank[i] = i;
            profit[i] = 0;
        }
        sort(rank + 1, rank + 1 + n, cmp);
        solve(1, n);
        printf("%.3f\n", ans);
    }
    return 0;
}
