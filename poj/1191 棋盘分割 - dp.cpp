#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;
const int inf = 1 << 30;
int n;
int dp[16][10][10][10][10];
int s[10][10];
int maz[10][10];

int cal(int x1, int y1, int x2, int y2) {
	int tmp = s[x2][y2] - s[x1-1][y2] - s[x2][y1-1] + s[x1-1][y1-1];
	return tmp * tmp;
}

int Dp(int k, int x1, int y1, int x2, int y2) {
	if(dp[k][x1][y1][x2][y2] != -1) return dp[k][x1][y1][x2][y2];
	if(k == 1) return dp[1][x1][y1][x2][y2] = cal(x1, y1, x2, y2);
	int tmp = inf;
	for(int a = x1; a < x2; a++) tmp = min(tmp, Dp(k-1, x1, y1, a, y2) + cal(a + 1, y1, x2, y2));
	for(int a = x1; a < x2; a++) tmp = min(tmp, Dp(k-1, a + 1, y1, x2, y2) + cal(x1, y1, a, y2));
	for(int b = y1; b < y2; b++) tmp = min(tmp, Dp(k-1, x1, y1, x2, b) + cal(x1, b + 1, x2, y2));
	for(int b = y1; b < y2; b++) tmp = min(tmp, Dp(k-1, x1, b + 1, x2, y2) + cal(x1, y1, x2, b));
	return dp[k][x1][y1][x2][y2] = tmp;
}

int main() {
	while(~scanf("%d", &n)) {
		double sum = 0;
		memset(dp, -1, sizeof(dp));
		memset(s, 0, sizeof(s));
		for(int i = 1; i < 9; i++) {
			for(int j = 1; j < 9; j++) {
				scanf("%d", &maz[i][j]);
				sum += maz[i][j];
			}
		}
		for(int i = 1; i < 9; i++) {
			for(int j = 1; j < 9; j++) {
				s[i][j] = maz[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
			}
		}
		sum /= n;
		double tmp = (double)Dp(n, 1, 1, 8, 8);
		double ans = sqrt(tmp / n - sum * sum);
		printf("%.3f\n", ans);
	}
	return 0;
}