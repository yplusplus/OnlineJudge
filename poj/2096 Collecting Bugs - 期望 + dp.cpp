#include "iostream"
#include "cstdio"
using namespace std;
#define max 1005
double dp[max][max];
int n, s;
/*
E[i][j] = 1 + (i*j/n/s) * E[i][j] + (i*(s-j)/n/s) * E[i][j+1]+
					((n-i)*j/n/s) * E[i+1][j] + (n-i)*(s-j)/n/s * E[i+1][j+1];
*/
int main() {
	cin >> n >> s;
	dp[n][s] = 0;
	for(int i = n; i >= 0; i--) {
		for(int j = s; j >= 0; j--) {
			if(i == n && j == s) continue;
            dp[i][j]=(n * s + (n-i) * j * dp[i+1][j] + i * (s-j) * dp[i][j+1] + (n-i) * (s-j) * dp[i+1][j+1]) / (n*s-i*j);
        }
    }
    printf("%.4f\n", dp[0][0]);
	return 0;
}
