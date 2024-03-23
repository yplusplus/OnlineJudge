#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
const double eps = 1e-8;
int n, m, k;
double p1, p2, p3, p4;
double dp[2010][2010], c[2010], p[2010];

void solve() {
	memset(dp, 0, sizeof(dp));
	double p21 = p2 / (1 - p1);
	double p31 = p3 / (1 - p1);
	double p41 = p4 / (1 - p1);
	dp[1][1] = p4 / (1 - p1 - p2);
	c[1] = p41;
	p[0] = 1;
	for(int i = 1; i <= n; i++) p[i] = p[i-1] * p21;//p[i] = p21 ^ i;
	for(int i = 2; i <= n; i++) {
		for(int j = 2; j <= k; j++) 
			c[j] = p31 * dp[i-1][j-1] + p41;
		for(int j = k + 1; j <= i; j++) 
			c[j] = p31 * dp[i-1][j-1];
		double tmp = c[i];
		for(int j = i - 1; j; j--) {
			tmp += p[i-j] * c[j];
		}
		dp[i][i] = tmp / (1 - p[i]);
		dp[i][1] = p21 * dp[i][i] + c[1];
		for(int j = 2; j <= i; j++) 
			dp[i][j] = p21 * dp[i][j-1] + c[j];
	}
	printf("%.5f\n", dp[n][m]);
}
int main() {
	while(~scanf("%d%d%d", &n, &m, &k)) {
		scanf("%lf%lf%lf%lf", &p1, &p2, &p3, &p4);
		if(p4 < eps) {//特判一下，如果p4很小直接输出0.00000
			puts("0.00000");
			continue;  
		} else solve();
	}
	return 0;
}