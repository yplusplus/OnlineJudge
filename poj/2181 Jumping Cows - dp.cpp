#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 150500
int dp[maxn][2];
int val[maxn];
int n;
int solve() {
	dp[0][0] = dp[0][1] = 0;
	for(int i = 1; i <= n; i++) {
		dp[i][0] = max(dp[i-1][0], dp[i-1][1] - val[i]);
		dp[i][1] = max(dp[i-1][1], dp[i-1][0] + val[i]);
	}
	return max(dp[n][0], dp[n][1]);
}

int main() {
	while(~scanf("%d", &n)) {
		for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
		int ans = solve();
		cout << ans << endl;
	}
	return 0;
}