#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 105
int n;
int main() {
	double sum, a[maxn];
	int Case = 1, T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		sum = 0;
		for(int i = 0; i < n; i++) {
			scanf("%lf", &a[i]);
			sum += a[i];
		}
		double ans = a[0] / sum;
		printf("Case %d: %.6f\n", Case++, ans);
	}
	return 0;
}
