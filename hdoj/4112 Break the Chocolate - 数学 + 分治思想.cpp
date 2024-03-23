#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;

#define ll long long

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while(T--) {
		ll n, m, k;
		scanf("%I64d%I64d%I64d", &n, &m, &k);
		ll ans1 = n * m * k - 1, ans2 = ceil(log(n * 1.0) / log(2.0)) + ceil(log(m * 1.0) / log(2.0)) + ceil(log(k * 1.0) / log(2.0));
		printf("Case #%d: %I64d %I64d\n", Case++, ans1, ans2);
	}
	return 0;
}