#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 111;
const int kind = 2;
int n, m, k;
const ll MOD = 1000000007LL;
ll add(ll a, ll b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}

struct Mat {
	ll val[kind][kind];
	void unit() {//µ¥Î»¾ØÕó
		zero();
		for(int i = 0; i < kind; i++) val[i][i] = 1;
	}
	void zero() {//Áã¾ØÕó
		memset(val, 0, sizeof(val));
	}
};

Mat operator*(const Mat &a, const Mat &b) {//¾ØÕó³Ë·¨
	Mat tmp;
	tmp.zero();
	for(int k = 0; k < kind; k++) {
		for(int i = 0; i < kind; i++)
			if(a.val[i][k])
				for(int j = 0; j < kind; j++) {
					tmp.val[i][j] += a.val[i][k] * b.val[k][j];
					if(tmp.val[i][j] >= MOD) tmp.val[i][j] %= MOD;
				}
	}
	return tmp;
}
Mat operator^(Mat x, int n) {//¾ØÕó¿ìËÙÃÝ
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
    while (cin >> n >> m >> k) {
        Mat a, b;
        a.zero();
        a.val[0][0] = k, a.val[0][1] = m - k;
        b.val[0][0] = k - 1, b.val[0][1] = m - k;
        b.val[1][0] = k, b.val[1][1] = m - k;
        Mat tmp = b ^ (--n);
        Mat ans = a * tmp;
        printf("%d\n", add(ans.val[0][0], ans.val[0][1]));
    }
    return 0;
}
