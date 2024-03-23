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
const double PI = acos(-1.0);
int d, a, u;
int main() {
    while(~scanf("%d%d%d", &u, &a, &d)) {
        if(!a) break;
        double aa = a / 180.0 * PI;
        double dd = d * 1.0;
        double uu = u * 1.0;
        int ans = int((exp(aa / sqrt(3.0) + log(dd)) - dd) / uu + 0.5);
        if(ans > 10000) printf("God help me!\n");
        else printf("%d\n", ans);
    }
    return 0;
}
