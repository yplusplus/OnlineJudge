#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define ll long long

ll gcd(ll a, ll b) {
	if(a % b == 0) return b;
	return gcd(b, a % b);
}

int main() {
	int T, n, m;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		scanf("%d%d", &n, &m);
		ll tmp = 1, x = 0;
		while(tmp < n) {
			tmp *= m;
			x++;
		}
		ll d = gcd(tmp * x, n);
		printf("Case %d: ", t);
		cout << tmp * x / d << "/" << n / d << endl;
	}
	return 0;
}
