#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 3050
int n, t;
double dp[maxn], p[maxn], q[maxn];

void solve() {
	dp[n] = 0;
	for(int i = n - 1; i >= 0; i--) {
		double c = p[i+1];
		double sum = t + 1 + q[i+1] + dp[i+1] * p[i+1];
		dp[i] = sum;
		for(int j = 2; j <= n - i; j++) {
			c *= p[i+j];
			sum = sum + 2 - c + c * dp[i+j] - c * dp[i+j-1];
			dp[i] = min(dp[i], sum);
		}
		dp[i] /= p[i+1];
	}
	printf("%.6f\n", dp[0]);
}

int main() {
	while(~scanf("%d%d", &n, &t)) {
		for(int i = 1; i <= n; i++) {
			scanf("%lf", &q[i]);
			p[i] = 1 - q[i];
		}
		solve();
	}
	return 0;
}
