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
#define maxn 20
double dp[1<<maxn];
double p[maxn];
int n;
int main() {
    while(~scanf("%d", &n)) {
        double pp = 0.0;
        for(int i = 0; i < n; i++) {
            scanf("%lf", &p[i]);
            pp += p[i];
        }
        pp = 1 - pp;
        int nn = 1 << n;
        dp[nn-1] = 0.0;
        for(int i = nn - 2; i >= 0; i--) {
            double sum = 1.0;
            double res = pp;
            for(int j = 0; j < n; j++) {
                if(i & (1 << j)) res += p[j];
                else sum += p[j] * dp[i | (1<<j)];
            }
            dp[i] = sum / (1 - res);
        }
        printf("%.8f\n", dp[0]);
    }
    return 0;
}
