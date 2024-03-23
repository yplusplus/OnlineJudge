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
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 30;
int k, m;
int dp[11][101][101];

void init_dp() {
    for(int r = 1; r <= 100; r++)
        for(int l = 1; l <= r; l++)
            dp[1][l][r] = (l + r) * (r - l + 1) / 2;

    for(int i = 2; i <= 10; i++) {
        for(int r = 1; r <= 100; r++) {
            for(int l = r; l; l--) {
                dp[i][l][r] = inf;
                for(int s = l; s <= r; s++) 
                    dp[i][l][r] = min(dp[i][l][r], s + max(dp[i][s+1][r], dp[i-1][l][s-1]));
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    init_dp();
    while(T--) {
        scanf("%d%d", &k, &m);
        printf("%d\n", dp[k][1][m]);
    }
    return 0;
}
