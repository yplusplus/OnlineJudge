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
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 1050
#define maxm 52
const int inf = 1 << 30;
const int gap = 9;
int dp[maxn][maxm][maxm];
int l, r, n, key;
int isqrt[100];

void init() {
    //抄了watashi的平方根预处理，写得太漂亮了
    for(int i = 0; i < 10; i++)
        for(int j = i * i; j < (i + 1) * (i + 1); j++)
            isqrt[j] = i;
}

int main() {
    while(~scanf("%d%d%d", &l, &r, &n)) {
        init();
        for(int k = 0; k < maxn; k++) 
            for(int i = 0; i < maxm; i++) 
                for(int j = 0; j < maxm; j++)
                    dp[k][i][j] = inf;
        dp[0][l][r] = 0;
        for(int now = 0; now < n; now++) {
            scanf("%d", &key);
            for(int i = 0; i < maxm; i++) {
                for(int j = 0; j < maxm; j++) {
                    if(dp[now][i][j] == inf) continue;
                    for(int k = key; k - key < gap && k < maxm; k++)
                        dp[now+1][k][j] = min(dp[now+1][k][j], dp[now][i][j] + isqrt[abs(i-k)]);
                    for(int k = key; key - k < gap && k >= 0; k--)
                        dp[now+1][i][k] = min(dp[now+1][i][k], dp[now][i][j] + isqrt[abs(j-k)]);
                }
            }
        }
        int ans = inf;
        for(int i = 0; i < maxm; i++)
            for(int j = 0; j < maxm; j++)
                ans = min(dp[n][i][j], ans);
        printf("%d\n", ans);
    }
    return 0;
}
