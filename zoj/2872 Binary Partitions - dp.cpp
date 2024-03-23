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
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 2000050
const int mod = 1000000;
int dp[maxn], n;
void init() {
    dp[0] = 1;
    for(int i = 1; i < maxn; i++) {
        dp[i] = (dp[i-1] + ((i&1) ? 0 : dp[i/2])) % mod;
    }
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        printf("%d\n", dp[n]);
    }
    return 0;

}
