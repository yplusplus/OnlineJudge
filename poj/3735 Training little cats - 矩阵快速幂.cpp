#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define ll long long
#define maxn 105
int n, m, k;
struct Mat {
	ll val[maxn][maxn];
	void zero() {
		memset(val, 0, sizeof(val));
	}
	void unit() {
		zero();
		for(int i = 0; i < maxn; i++) val[i][i] = 1;
	}
}A, T;//A = ³õÊ¼¾ØÕó ,T = ×ªÖÃ¾ØÕó

Mat operator *(const Mat &a, const Mat &b) {
	Mat tmp;
	tmp.zero();
	for(int k = 0; k <= n; k++) {
		for(int i = 0; i <= n; i++) {
			if(a.val[i][k])
				for(int j = 0; j <= n; j++)
					tmp.val[i][j] += a.val[i][k] * b.val[k][j];
		}
	}
	return tmp;
}

Mat operator ^(Mat x, int n) {
	Mat tmp;
	tmp.unit();
	while(n) {
		if(n & 1) tmp = tmp * x;
		x = x * x;
		n >>= 1;
	}
	return tmp;
}

void init() {
	A.zero();
	A.val[0][0] = 1;
	T.unit();
}

int main() {
	char s[5];
	int a, b;
	while(~scanf("%d%d%d", &n, &m, &k)) {
		if(!n && !m && !k) break;
		init();
		for(int i = 0; i < k; i++) {
			scanf("%s", s);
			if(s[0] == 'g') {
				scanf("%d", &a);
				T.val[0][a]++;
			} else if(s[0] == 'e') {
				scanf("%d", &a);
				for(int i = 0; i <= n; i++) T.val[i][a] = 0;
			} else {
				scanf("%d%d", &a, &b);
				for(int i = 0; i <= n; i++) swap(T.val[i][a], T.val[i][b]);
			}
		}
		Mat ans = A * (T ^ m);
		for(int i = 1; i <= n; i++) printf("%lld ", ans.val[0][i]);
		printf("\n");
	}
	return 0;
}