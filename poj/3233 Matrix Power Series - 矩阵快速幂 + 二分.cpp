#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
#define maxn 35
int n, k, m;
struct Mat {
	int val[maxn][maxn];
	void unit() {//µ•Œªæÿ’Û
		for(int i = 0; i < maxn; i++) val[i][i] = 1;
	}
	void zero() {//¡„æÿ’Û
		memset(val, 0, sizeof(val));
	}
}x;

Mat operator *(const Mat &a, const Mat &b) {//æÿ’Û≥À∑®
	Mat tmp;
	tmp.zero();
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++)
			if(a.val[i][k])
				for(int j = 1; j <= n; j++) {
					tmp.val[i][j] += a.val[i][k] * b.val[k][j];
					if(tmp.val[i][j] >= m) tmp.val[i][j] %= m;
				}
	}
	return tmp;
}

Mat operator ^(Mat x, int n) {//æÿ’ÛøÏÀŸ√›
	Mat tmp;
	tmp.zero();
	tmp.unit();
	while(n) {
		if(n & 1) tmp = tmp * x;
		x = x * x;
		n >>= 1;
	}
	return tmp;
}

Mat operator +(const Mat &a, const Mat &b) {//æÿ’Ûº”∑®
	Mat tmp;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			tmp.val[i][j] = (a.val[i][j] + b.val[i][j]) % m;
	return tmp;
}

Mat sum(int k) {
	if(k == 1) return x;
	else {
		Mat tmp = sum(k >> 1);
		if(k & 1) {
			Mat tmp2 = x ^ ((k >> 1) + 1);
			return tmp + tmp2 + tmp * tmp2;
		} else {
			Mat tmp2 = x ^ (k >> 1);
			return tmp + tmp * tmp2;
		}
	}
}

int main() {
	while(~scanf("%d%d%d", &n, &k, &m)) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				scanf("%d", &x.val[i][j]);
				x.val[i][j] %= m;
			}
		}
		Mat ans = sum(k);
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j < n; j++) 
				printf("%d ", ans.val[i][j]);
			printf("%d\n", ans.val[i][n]);
		}
		break;
	}
	return 0;
}