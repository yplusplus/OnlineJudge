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
#define MAX 510
double x[MAX], y[MAX], p[20];
int n, k1, k2, k3, a, b, c;
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d%d%d%d%d", &n, &k1, &k2, &k3, &a, &b, &c);
        int tot = k1 + k2 + k3;
        double pp = 1.0 / k1 / k2 / k3;
        memset(p, 0, sizeof(p));
        for(int i = 1; i <= k1; i++)
            for(int j = 1; j <= k2; j++)
                for(int k = 1; k <= k3; k++)
                    p[i+j+k] += pp;
        p[a+b+c] -= pp;
        for(int i = n; i >= 0; i--) {
            x[i] = pp, y[i] = 1.0;
            for(int j = 3; j <= tot && i + j <= n; j++) {
                x[i] += p[j] * x[i+j];
                y[i] += p[j] * y[i+j];
            }
        }
        printf("%.15f\n", y[0] / (1.0 - x[0]));
    }
    return 0;
}
