#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
const int MOD = 100000000;
int r, c;
int maz[15][15];
int row[15];
int dp[15][1<<15];
bool ok[1<<15];

void solve() {
	memset(ok, true, sizeof(ok));
	for(int i = 0; i < (1 << c); i++) {
		for(int j = 0; j < c - 1; j++) {
			if((i & (1 << j)) && (i & (1 << (j + 1)))) {
				ok[i] = false;
				break;
			}
		}
		if(ok[i]) dp[0][i] = 1;
	}
	for(int i = 0; i < r - 1; i++) {
		for(int j = 0; j < (1 << c); j++) {
			if(ok[j] && ((j & row[i]) == 0)) {
				for(int k = 0; k < (1 << c); k++) {
					if(ok[k] && ((row[i+1] & k) == 0) && ((j & k) == 0)) dp[i+1][k] += dp[i][j];
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < (1 << c); i++)
		if(ok[i] && ((i & row[r-1]) == 0)) ans = (ans + dp[r-1][i]) % MOD;
	cout << ans << endl;
	return;
}

int main() {
	while(~scanf("%d%d", &r, &c)) {
		memset(row, 0, sizeof(row));
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				scanf("%d", &maz[i][j]);
				if(!maz[i][j]) row[i] |= (1 << j); 
			}
		}
		solve();
	}
	return 0;
}