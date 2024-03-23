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
#define MAX 100050
int n, m;
struct Ticket {
    int u, v;
    double st, ti, p, d;
    bool operator<(const Ticket &x) const {
        return st > x.st;
    }
}t[MAX];
vector<pdd> vec[MAX];
int main() {
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%lf%lf%lf%lf", &t[i].u, &t[i].v, &t[i].st, &t[i].ti, &t[i].p, &t[i].d);
            t[i].p /= 100.0;
        }
        sort(t, t + m);
        for(int i = 0; i < m; i++) {
            int u = t[i].u, v = t[i].v;
            if(v == n) {
                double st = t[i].st;
                double e = t[i].st + t[i].ti + t[i].p * t[i].d;
                if(vec[u].size() == 0 || vec[u].back().se > e) vec[u].pb(mp(st, e));
            } else {
                int l, r, idx;
                double st = t[i].st;
                double e = 0.0;
                double res = t[i].st + t[i].ti + t[i].d;
                //delay
                l = 0, r = vec[v].size() - 1;
                idx = -1;
                while(l <= r) {
                    int mid = (l + r) >> 1;
                    if(vec[v][mid].fi >= res) idx = mid, l = mid + 1;
                    else r = mid - 1;
                }
                if(idx == -1) continue;
                e += vec[v][idx].se * t[i].p;
                //not delay
                l = 0, r = vec[v].size() - 1;
                idx = -1;
                res -= t[i].d;
                while(l <= r) {
                    int mid = (l + r) >> 1;
                    if(vec[v][mid].fi >= res) idx = mid, l = mid + 1;
                    else r = mid - 1;
                }
                e += vec[v][idx].se * (1.0 - t[i].p);
                if(vec[u].size() == 0 || vec[u].back().se > e) vec[u].pb(mp(st, e));
            }
        }
        if(vec[1].size() == 0) puts("Fail");
        else printf("%.8f\n", vec[1].back().se);
    }
    return 0;
}
