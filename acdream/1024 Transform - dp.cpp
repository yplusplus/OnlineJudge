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

const int N = 111111;
int dp[N];
int main() {
    int a, b;
    while(~scanf("%d%d", &a, &b)) {
        memset(dp, -1, sizeof(dp));
        if(a > b) puts("-1");
        else {
            dp[a] = 0;
            for(int i = a; i < b; i++) {
                int tmp = (int)sqrt((double)(i));
                for(int j = 1; j <= tmp; j++) {
                    if(i % j == 0) {
                        if(i + j <= b && (dp[i + j] == -1 || dp[i + j] > dp[i] + 1)) {
                            dp[i + j] = dp[i] + 1;
                        }
                        int jj = i / j;
                        if(i + jj <= b && (dp[i + jj] == -1 || dp[i + jj] > dp[i] + 1)) {
                            dp[i + jj] = dp[i] + 1;
                        }
                    }
                }
            }
            printf("%d\n", dp[b]);
        }
    }
    return 0;
}
