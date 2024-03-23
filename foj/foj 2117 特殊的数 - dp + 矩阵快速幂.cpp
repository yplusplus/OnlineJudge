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
ll n;
const ll MOD = 1000000007LL;
const int kind = 4;
struct Mat {
	ll val[kind][kind];
    Mat() {
		memset(val, 0, sizeof(val));
    }
	void unit() {//µ¥Î»¾ØÕó
		for(int i = 0; i < kind; i++) val[i][i] = 1;
	}
}mat[70];

Mat operator *(const Mat &a, const Mat &b) {//¾ØÕó³Ë·¨
	Mat tmp;
    for(int k = 0; k < kind; k++) 
        for(int i = 0; i < kind; i++)
            if (a.val[i][k]) {
            for(int j = 0; j < kind; j++) {
                tmp.val[i][j] += a.val[i][k] * b.val[k][j];
                if(tmp.val[i][j] >= MOD) tmp.val[i][j] %= MOD;
            }
        }
    return tmp;
}
Mat operator ^(Mat x, ll n) {//¾ØÕó¿ìËÙÃÝ
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
    const ll val[kind][kind] = {3, 1, 1, 0, 1, 3, 0, 1, 1, 0, 3, 1, 0, 1, 1, 3};
    memcpy(mat[0].val, val, sizeof(val));

    for (int i = 1; i < 65; i++) {
        mat[i] = mat[i - 1] * mat[i - 1];
    }
    cin >> T;
    while (T--) {
        cin >> n;
        Mat b;
        b.val[0][0] = 1;
        for (int i = 0; i < 62; i++) {
            if (n >> i & 1) b = b * mat[i];
        }
        cout << b.val[0][0] << endl;
    }
    return 0;
}
