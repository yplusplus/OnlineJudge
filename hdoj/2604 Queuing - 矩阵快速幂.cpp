#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define MAX 4
int l, m;
struct Mat {
	int val[MAX][MAX];
	void init() {
		zero();
		val[0][0] = val[0][1] = val[1][2] = val[1][3] = val[2][0] = val[3][2] = 1;
	}
	void unit() {
		zero();
		for(int i = 0; i < MAX; i++) val[i][i] = 1;
	}
	void zero() {
		memset(val, 0, sizeof(val));
	}
};

Mat operator *(const Mat &a, const Mat &b) {
	Mat tmp;
	tmp.zero();
	for(int k = 0; k < MAX; k++) {
		for(int i = 0; i < MAX; i++) {
			if(a.val[i][k])
				for(int j = 0; j < MAX; j++) {
					tmp.val[i][j] += a.val[i][k] * b.val[k][j];
					if(tmp.val[i][j] >= m) tmp.val[i][j] %= m;
				}
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

int main() {
	while(~scanf("%d%d", &l, &m)) {
		Mat tmp;
		tmp.init();
		Mat ans = tmp ^ l;
		int res = 0;
		for(int i = 0; i < MAX; i++) {
			res += ans.val[0][i];
		}
		printf("%d\n", res % m);
	}
	return 0;
}
