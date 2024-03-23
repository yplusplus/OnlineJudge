#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 110
const int MOD = 9973;
int n, k;

struct Mat {
	int val[maxn][maxn];
	void unit() {//µ¥Î»¾ØÕó
		zero();
		for(int i = 0; i < maxn; i++) val[i][i] = 1;
	}
	void zero() {//Áã¾ØÕó
		memset(val, 0, sizeof(val));
	}
};

Mat operator *(const Mat &a, const Mat &b) {//¾ØÕó³Ë·¨
	Mat tmp;
	tmp.zero();
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++)
			if(a.val[i][k])
				for(int j = 1; j <= n; j++) {
					tmp.val[i][j] += a.val[i][k] * b.val[k][j];
					if(tmp.val[i][j] >= MOD) tmp.val[i][j] %= MOD;
				}
	}
	return tmp;
}
Mat operator ^(Mat x, int n) {//¾ØÕó¿ìËÙÃÝ
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
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        Mat x;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &x.val[i][j]);
            }
        }
        x = x ^ k;
        int ans = 0;
        for(int i = 1; i <= n; i++) 
            ans += x.val[i][i];
        cout << ans % MOD << endl;
    }
    return 0;
}
