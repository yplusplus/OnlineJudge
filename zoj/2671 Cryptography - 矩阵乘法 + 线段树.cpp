#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 32768
int r, n, m;
struct Mat {
	int val[2][2];
	void zero() {
		memset(val, 0, sizeof(val));
	}
}x[(maxn<<1)+1];

int LC(int i) {return i << 1;}
int RC(int i) {return LC(i)^1;}

Mat operator *(const Mat &a, const Mat &b) {
	Mat tmp;
	tmp.zero();
	for(int k = 0; k < 2; k++) {
		for(int i = 0; i < 2; i++) {
			if(a.val[i][k]) {
				for(int j = 0; j < 2; j++) {
					tmp.val[i][j] += a.val[i][k] * b.val[k][j];
					if(tmp.val[i][j] >= r) tmp.val[i][j] %= r;
				}
			}
		}
	}
	return tmp;
}

Mat query(int p, int left, int right, int l, int r) {//线段树的查询思想
	if(left == l && right == r) return x[p];
	int mid = (left + right) >> 1;
	if(r <= mid) return query(LC(p), left, mid, l, r);
	else if(l > mid) return query(RC(p), mid + 1, right, l, r);
	else return query(LC(p), left, mid, l, mid) * query(RC(p), mid + 1, right, mid + 1, r);
}

int main() {
	bool flag = false;
	while(~scanf("%d%d%d", &r, &n, &m)) {
		int st = 1;
		while(st < n) st <<= 1;
		for(int i = 0; i < n; i++) 
			for(int j = 0; j < 2; j++)
				for(int k = 0; k < 2; k++)
					scanf("%d", &x[st+i].val[j][k]);
		for(int i = st - 1; i; i--) x[i] = x[LC(i)] * x[RC(i)];
		while(m--) {
			if(flag) printf("\n");
			else flag = true;
			int le, ri;
			scanf("%d%d", &le, &ri);
			Mat ans = query(1, 1, st, le, ri);
			printf("%d %d\n%d %d\n", ans.val[0][0], ans.val[0][1], ans.val[1][0], ans.val[1][1]);
		}
	}
	return 0;
}