#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 50
int dp[maxn][2];
int main() {
	int T, n;
	dp[1][0] = dp[1][1] = 1;
	for(int i = 2; i < maxn; i++) {
		dp[i][0] = dp[i-1][0] + dp[i-1][1];
		dp[i][1] = dp[i-1][0];
	}
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		scanf("%d", &n);
		int ans = dp[n][0] + dp[n][1];
		printf("Scenario #%d:\n", t);
		printf("%d\n\n", ans);
	}
	return 0;
}