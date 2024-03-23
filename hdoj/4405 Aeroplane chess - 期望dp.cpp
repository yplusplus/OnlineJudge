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
int n, m;
double dp[maxn];
int next[maxn];
int main() {
    while(~scanf("%d%d", &n, &m)) {
        if(!n && !m) break;
        memset(next, -1, sizeof(next));
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            next[a] = b;
        }
        for(int i = n - 1; i >= 0; i--) {
            if(next[i] != -1) {
                dp[i] = dp[next[i]];
            } else {
                dp[i] = 1.0;
                for(int j = 1; j <= 6; j++) {
                    dp[i] += dp[i + j] / 6.0;
                }
            }
        }
        printf("%.4f\n", dp[0]);
    }
    return 0;
}
