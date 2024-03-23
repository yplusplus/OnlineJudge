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
#define maxn 100050
ll costa[maxn], costb[maxn];
int pa, pb;
int a[maxn], b[maxn];
int anscnt, anscost;
int n, initValue;
void update(int &anscnt, int &anscost, int tmpcnt, int tmpcost) {
    if(tmpcnt > anscnt) {
        anscnt = tmpcnt, anscost = tmpcost;
    } else if(tmpcnt == anscnt && tmpcost < anscost) {
        anscost = tmpcost;
    }
}

int bsearch(int l, int r, int x) {
    int res = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(costa[mid] <= x) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}

int main() {
    int Case = 1, T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &initValue);
        int sum = 0;
        pa = pb = 0;
        anscnt = 0, anscost = initValue;
        for(int i = 0; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            if(y == 0) {
                a[++pa] = x;
            } else {
                sum += y;
                b[++pb] = x;
            }
        }
        sort(a + 1, a + 1 + pa);
        sort(b + 1, b + 1 + pb);
        costa[0] = costb[0] = 0;
        for(int i = 1; i <= pa; i++) {
            costa[i] = costa[i-1] + a[i];
        }
        for(int i = 1; i <= pb; i++) {
            costb[i] = costb[i-1] + b[i];
        }
        int tmp = bsearch(0, pa, initValue);
        update(anscnt, anscost, tmp, costa[tmp]);
        for(int i = 1; i <= pb; i++) {
            if(initValue < costb[i]) break;
            int tmpsum = sum - (pb - i);
            if(tmpsum >= pa) {
                update(anscnt, anscost, n, costb[i]);
            } else {
                int res = bsearch(0, pa - tmpsum, initValue - costb[i]);
                update(anscnt, anscost, pb + res + tmpsum, costb[i] + costa[res]);
            }
        }
        printf("Case %d: %d %d\n", Case++, anscnt, anscost);
    }
    return 0;
}
