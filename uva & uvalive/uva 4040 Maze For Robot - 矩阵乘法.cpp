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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 110
int n, l;
int q[maxn], tot;
struct Mat {
	ll val[maxn][maxn];
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
        tot = 0;
        scanf("%d", &n);
        Mat a, b, c;
        int u, v;
        a.unit(), b.zero();
        for(int i = 1; i <= n; i++) {
            scanf("%d", &u);
            for(int j = 0; j < 3; j++) {
                scanf("%d", &v);
                b.val[u][v]++;
            } 
            scanf("%d", &v);
            if(v) q[tot++] = u;
        }
        scanf("%d", &l);
        c = a * (b ^ l);
        ll ans = 0;
        for(int i = 0; i < tot; i++) {
            ans += c.val[1][q[i]];
        }
        cout << ans << endl;
    }
    return 0;
}
