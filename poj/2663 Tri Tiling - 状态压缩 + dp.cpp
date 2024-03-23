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
const int N = 33;
int dp[N][8];
int n;
int main() {
    memset(dp, 0, sizeof(dp));
    dp[0][7] = 1;
    for(int i = 0; i <= 30; i++) {
        //000
        dp[i+1][4] += dp[i][0];
        dp[i+1][1] += dp[i][0];
        dp[i+1][7] += dp[i][0];
        //001
        dp[i+1][0] += dp[i][1];
        dp[i+1][6] += dp[i][1];
        //010
        dp[i+1][5] += dp[i][2];
        //011
        dp[i+1][4] += dp[i][3];
        //100
        dp[i+1][0] += dp[i][4];
        dp[i+1][3] += dp[i][4];
        //101
        dp[i+1][2] += dp[i][5];
        //110
        dp[i+1][1] += dp[i][6];
        //111
        dp[i+1][0] += dp[i][7];
    }
    while(~scanf("%d", &n)) {
        if(n == -1) break;
        cout << dp[n+1][0] << endl;
    }
    return 0;
}
