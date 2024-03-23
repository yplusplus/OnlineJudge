#include "iostream"
#include "cstdio"
using namespace std;

int main() {
	double x, sum;
	int i;
	while(1) {
		scanf("%lf", &x);
		if(x < 1e-8) break;
		sum = 0;
		for(i = 2; ; i++) {
			sum += 1 / (double)i;
			if(sum > x) break;
		}
		printf("%d card(s)\n", i - 1);
	}
	return 0;
}