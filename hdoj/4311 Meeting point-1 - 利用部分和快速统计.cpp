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
#define maxn 100050
const ll linf = 1LL << 50;
struct Point {
    ll x, y, id;
}p[maxn];

bool cmpx(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool cmpy(const Point &a, const Point &b) {
    return a.y < b.y;
}

ll sx[maxn], sy[maxn];
ll sumx, sumy;
ll res[maxn];
int n;
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        sumx = sumy = 0;
        scanf("%d", &n);
        p[0].id = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%I64d%I64d", &p[i].x, &p[i].y);
            sumx += p[i].x;
            sumy += p[i].y;
            p[i].id = i;
        }
        memset(res, 0, sizeof(res));
        sx[0] = sy[0] = 0;
        sort(p + 1, p + 1 + n, cmpx);
        for(int i = 1; i <= n; i++) {
            sx[p[i].id] = sx[p[i-1].id] + p[i].x;
            res[p[i].id] += ((i - 1) * p[i].x - sx[p[i-1].id]) + ((sumx - sx[p[i].id]) - (n - i) * p[i].x);
        }
        sort(p + 1, p + 1 + n, cmpy);
        for(int i = 1; i <= n; i++) {
            sy[p[i].id] = sy[p[i-1].id] + p[i].y;
            res[p[i].id] += ((i - 1) * p[i].y - sy[p[i-1].id]) + ((sumy - sy[p[i].id]) - (n - i) * p[i].y);
        }
        ll ans = linf;
        for(int i = 1; i <= n; i++) {
            ans = min(ans, res[i]);
        }
        cout << ans << endl;
    }
    return 0;
}
