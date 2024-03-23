#include "iostream"
using namespace std;
#define maxv 305
int v, p;
int vill[maxv], dist[maxv][maxv], dp[maxv][maxv];
const int INF = 99999999;

int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	int i, j, k;
	scanf("%d%d", &v, &p);
	for(i = 1; i <= v; i++)
		scanf("%d", &vill[i]);
	for(i = 1; i <= v; i++) {
		dist[i][i] = 0;
		for(j = i + 1; j <= v; j++)
			dist[i][j] = dist[i][j-1] + vill[j] - vill[(i+j)/2];
		dp[i][1] = dist[1][i];
	}
	for(j = 2; j <= p; j++) {
		for(i = j + 1; i <= v; i++) {
			dp[i][j] = INF;
			for(k = j - 1; k <= i - 1; k++)
				dp[i][j] = min(dp[i][j], dp[k][j-1] + dist[k+1][i]);
		}
	}
	printf("%d\n", dp[v][p]);
	return 0;
}
