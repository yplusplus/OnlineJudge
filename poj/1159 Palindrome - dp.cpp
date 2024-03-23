#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
#define maxn 5050
char s[maxn], t[maxn];
int n;
int dp[2][maxn];
void solve() {
    for(int i = 0; i < n; i++) t[i] = s[n - 1 - i];
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int idx = i % 2, idx2 = (i + 1) % 2;
            if(s[i-1] == t[j-1]) dp[idx][j] = dp[idx2][j-1] + 1;
            else dp[idx][j] = max(dp[idx2][j], dp[idx][j-1]);
        }
    }
    printf("%d\n", n - dp[n%2][n]);
}

int main() {
    while(~scanf("%d", &n)) {
        scanf("%s", s);
        solve();
    }
    return 0;
}
