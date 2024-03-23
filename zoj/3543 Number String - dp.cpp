#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 1010
const int MOD = 1000000007;
char s[maxn];
int dp[maxn][maxn], sum[maxn][maxn];

void solve() {
	int len = strlen(s+2);
	memset(dp, 0, sizeof(dp));
	memset(sum, 0, sizeof(sum));
	dp[1][1] = sum[1][1] = 1;
	for(int i = 2; i < len + 2; i++) {
		for(int j = 1; j <= i; j++) {
			if(s[i] == 'I') dp[i][j] = sum[i-1][j-1];
			else if(s[i] == 'D') dp[i][j] = (sum[i-1][i-1] - sum[i-1][j-1] + MOD) % MOD;
			else dp[i][j] = sum[i-1][i-1];
			sum[i][j] = (sum[i][j-1] + dp[i][j]) % MOD;
		}
	}
	printf("%d\n", sum[len+1][len+1]);
}

int main() {
	while(~scanf("%s", s + 2)) solve();
	return 0;
}
