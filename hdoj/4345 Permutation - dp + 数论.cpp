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
#define maxn 1010
int pri[maxn], pn;
bool ispri[maxn];
ll dp[maxn][maxn];
int n;
void get_prime() {
    memset(ispri, true, sizeof(ispri));
    pn = 1;
    for(int i = 2; i < maxn; i++) {
        if(ispri[i]) {
            pri[pn++] = i;
            for(int j = i * i; j < maxn; j += i) ispri[j] = false;
        }
    }
}

void init() {
    get_prime();
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i <= 1000; i++) dp[0][i] = 1;
    for(int i = 1; i < pn; i++) {
        for(int j = 0; j <= 1000; j++) {
            dp[i][j] += dp[i-1][j];
            for(int k = pri[i]; k <= j; k *= pri[i]) {
                dp[i][j] += dp[i-1][j-k];
            }
        }
    }
}

int main() {
    init();
    while(~scanf("%d", &n)) {
        printf("%I64d\n", dp[pn-1][n]);
    }
    return 0;
}
