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
#define MAX 365
ll dp[MAX][MAX];
const ll mod = 1000000007LL;
int n, d;
ll C[MAX][MAX], sum[MAX][MAX];

bool check(int n, int d) {
    if(d >= 9) return n >= d;
    else return ((1 << d) - 1 >= n) && n >= d;
}

void init() {
    memset(C, 0, sizeof(C));
    for(int i = 0; i < MAX; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
    }
    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));
    dp[1][1] = 1, dp[0][0] = 1;
    sum[0][0] = 1;
    for(int i = 1; i < MAX; i++) sum[0][i] = sum[1][i] = 1;
    for(int i = 2; i < MAX; i++) {
        for(int j = 2; j < MAX; j++) {
            if(!check(i, j)) {
                sum[i][j] = sum[i][j-1];
                continue;
            }
            ll res = 0;
            //only one subtree
            if(check(i - 1, j - 1)) res += dp[i-1][j-1] * 2 % mod;
            //has two subtrees
            for(int k = j - 1; k < i - 1; k++) {
                //left 
                res += (((dp[k][j-1] * sum[i-1-k][j-1]) % mod) * C[i-2][k]) % mod;
                //right
                res += (((dp[k][j-1] * sum[i-1-k][j-2]) % mod) * C[i-2][i-1-k]) % mod;
            }
            dp[i][j] = (res * i) % mod;
            sum[i][j] = (sum[i][j-1] + dp[i][j]) % mod;
        }
    }
}


int main() {
    init();
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &d);
        printf("Case #%d: %I64d\n",Case++, dp[n][d]);
    }
    return 0;
}
