#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define MAX 3
const int MOD = 10000;
struct Mat {
	int val[MAX][MAX];
	void unit() {
		for(int i = 0; i < MAX; i++) val[i][i] = 1;
	}
	void zero() {
		memset(val, 0, sizeof(val));
	}
};

Mat operator *(const Mat &a, const Mat &b) {
	Mat tmp;
	tmp.zero();
	for(int k = 1; k < MAX; k++) {
		for(int i = 1; i < MAX; i++) {
			if(a.val[i][k])
				for(int j = 1; j < MAX; j++) {
					tmp.val[i][j] += a.val[i][k] * b.val[k][j];
					if(tmp.val[i][j] >= MOD) tmp.val[i][j] %= MOD;
				}
		}
	}
	return tmp;
}

Mat operator ^(Mat x, int n) {
	Mat tmp;
	tmp.zero(), tmp.unit();
	while(n) {
		if(n & 1) tmp = tmp * x;
		x = x * x;
		n >>= 1;
	}
	return tmp;
}

int main() {
	Mat x;
	int n;
	x.val[1][1] = x.val[1][2] = x.val[2][1] = 1, x.val[2][2] = 0;
	while(~scanf("%d", &n)) {
		if(n == -1) break;
		Mat ans = x ^ n;
		printf("%d\n", ans.val[1][2]);
	}
	return 0;
}
