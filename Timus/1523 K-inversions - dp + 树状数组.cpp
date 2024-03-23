#include "iostream"
#include "cstdio"
using namespace std;
#define maxn 20005
#define maxk 15
#define MOD 1000000000
// dp[k][i] = ¡Æd[k-1][j], 1 <= j < i ÇÒ a[j] > a[i];
int n, k;
int dp[maxk][maxn], a[maxn];
int c[maxk][maxn];
int lowbit(int i) {
	return i & -i;
}

void update(int i, int k, int v) {
	for(; i <= n; i += lowbit(i)) c[k][i] = (c[k][i] + v) % MOD;
}

int sum(int i, int k) {
	int res = 0;
	for(; i; i -= lowbit(i)) res = (res + c[k][i]) % MOD;
	return res;
}

int main() {
	int i, j;
	__int64 ans = 0;
	cin >> n >> k;
	for(i = 1; i <= n; i++) cin >> a[i];
	fill(&dp[1][0], &dp[1][maxn-1], 1);
	for(j = 1; j <= n; j++) {
		update(a[j], 1, dp[1][j]);
		for(i = 2; i <= k; i++){
			dp[i][j] = (sum(n, i-1) - sum(a[j], i-1) + MOD) % MOD;
			update(a[j], i, dp[i][j]);
		}
		ans = (ans + dp[k][j]) % MOD;
	}
	printf("%I64d\n", ans);
	return 0;
}

