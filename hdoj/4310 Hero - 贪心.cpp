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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
pii p[30];
bool cmp(const pii &a, const pii &b) {
    return a.fi * b.se > b.fi * a.se;
}

int main() {
    int n, a, b;
    while(~scanf("%d", &n)) {
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &a, &b);
            p[i] = mp(a, b);
        }
        sort(p, p + n, cmp);
        int ans = 0;
        int ti = 0;
        for(int i = 0; i < n; i++) {
            ans += (ti + p[i].se) * p[i].fi;
            ti += p[i].se;
        }
        cout << ans << endl;
    }
    return 0;
}
