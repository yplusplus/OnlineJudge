#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
double p[1050][50];
int n, m, t;
double dp[1050][35][35];
double solve() {
	for(int i = 1; i <= t; i++) {
		dp[i][0][0] = 1;
		for(int j = 1; j <= m; j++) {
			for(int k = 0; k <= j; k++) {
				if(k) dp[i][j][k] = dp[i][j-1][k-1] * p[i][j] + dp[i][j-1][k] * (1 - p[i][j]);
				else dp[i][j][k] = dp[i][j-1][k] * (1 - p[i][j]);
			}
		}
	}
	double p1 = 1, p2 = 1;
	for(int i = 1; i <= t; i++) {
		double tmp = 0;
		for(int j = 1; j <= m; j++) {
			tmp += dp[i][m][j];
		}
		p1 *= tmp;
	}
	for(int i = 1; i <= t; i++) {
		double tmp = 0;
		for(int j = 1; j < n; j++) {
			tmp += dp[i][m][j];
		}
		p2 *= tmp;
	}
	return p1 - p2;
}

int main() {
	while(scanf("%d%d%d", &m, &t, &n)) {
		if(!m && !n && !t) break;
		for(int i = 1; i <= t; i++) {
			for(int j = 1; j <= m; j++) {
				scanf("%lf", &p[i][j]);
			}
		}
		printf("%.3f\n", solve());
	}
	return 0;
}