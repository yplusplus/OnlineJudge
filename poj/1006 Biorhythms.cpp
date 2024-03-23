#include "iostream"
using namespace std;

int main() {
	int p, e, i, d;
	int t = 1;
	while(cin >> p >> e >> i >> d) {
		if(p == -1 && e == -1 && i == -1 && d == -1) break;
		int ans = 0, mod = 23 * 28 * 33;
		ans = (5544 * p + 14421 * e + 1288 * i - d + mod) % mod;
		if(ans == 0) ans = mod;
		printf("Case %d: the next triple peak occurs in %d days.\n", t++, ans);
	}
	return 0;
}