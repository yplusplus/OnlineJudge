#include"iostream"
#include"cmath"
#include"cstdio"
#include"cstring"
using namespace std;
#define bigint __int64
//扩展欧几里德算法 d=gcd(a, b) 不定方程：ax+by=gcd(a,b)
void exGcd(bigint a, bigint b, bigint &d, bigint &x, bigint &y) {
	if(b == 0)
		d = a, x = 1, y = 0;
    else {
        exGcd(b, a % b, d, y, x);
        y -= x * (a/b);
	}
}

int main()
{
	bigint x, y, m, n, l;
	bigint xx, yy;
	while(scanf("%I64d%I64d%I64d%I64d%I64d", &x, &y, &m, &n, &l)!=EOF) {
		bigint d;
		bigint a = n - m;
		bigint b = l;
		bigint c = x - y;

		if(a<0) {
			a = m - n;
			c = y - x;
		}
		exGcd(a, b, d, xx, yy);
		if((x-y) % d != 0) cout << "Impossible" << endl;
		else {
			b /= d;
			xx = (xx * c / d) % b;
			printf("%I64d\n", (xx + b) % b);
		}
	}
	return 0;
}
