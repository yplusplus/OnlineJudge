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
#define maxn 110
int c[maxn];
int n, f;
double dp[22222];
double t[maxn];
int main() {
    while(~scanf("%d%d", &n, &f)) {
        int maxC = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &c[i]);
            maxC = max(maxC, c[i]);
            t[i] = floor((1.0 + sqrt(5.0)) / 2.0 * c[i] * c[i]);
        }
        double res = 0.0;
        for(int j = 0; j < n; j++) res += (t[j]) / n;
        memset(dp, 0, sizeof(dp));
        for(int i = 22222; i > maxC; i--) {
            dp[i] = res;
        }
        for(int i = maxC; i >= f; i--) {
            for(int j = 0; j < n; j++) {
                if(i > c[j]) dp[i] += (t[j]) / n;
                else dp[i] += (1.0 + dp[i+c[j]]) / n;
            }
        }
        printf("%.3f\n", dp[f]);
    }
    return 0;
}
