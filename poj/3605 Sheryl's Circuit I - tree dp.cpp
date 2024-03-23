#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 20500
int n;
char signal[20000];
int op[maxn], cnt;
int dp[maxn][2];

int solve() {
	memset(dp, 0, sizeof(dp));
	cnt = 0;
	while(n >> cnt != 1) cnt++;
	for(int i = 1 << cnt; i < 1 << (cnt + 1); i++) dp[i][1] = 1;
	for(int i = (1 << cnt) - 1; i; i--) {
			if(op[i]) {
				dp[i][0] = min(dp[2 * i][0], dp[2 * i + 1][0]);
				dp[i][1] = dp[2 * i][1] + dp[2 * i + 1][1];
			} else {
				dp[i][0] = dp[2 * i][0] + dp[2 * i + 1][0];
				dp[i][1] = min(dp[2 * i][1], dp[2 * i + 1][1]);
			}
	}
	return dp[1][1];
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		scanf("%s", signal);
		for(int i = 1; i < n; i++) scanf("%d", &op[i]);
		int ans = solve(), len = strlen(signal);
		cnt = 0;
		if(len == 0) {
			cout << ((signal[0] - '0') ? ans : 0) << endl;
			continue;
		}
		for(int i = 1; i < len; i++) 
			if(signal[i] != signal[i-1]) cnt++;
		if(signal[0] -'0') ans += cnt;
		else ans += cnt - 1;
		cout << ans << endl;
	}
	return 0;
}
