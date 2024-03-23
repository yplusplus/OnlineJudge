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

//好明显的状态压缩dp，然后可以矩阵快速幂优化，手写了个高精度，代码写的好恶心。。。。

const int M = 1 << 5;
int all, MOD, m;
int row[111], len;
struct Mat {
    int val[M][M];
    Mat() {
        memset(val, 0, sizeof(val));
    }
    void unit() {
        for(int i = 0; i < M; i++) {
            val[i][i] = 1;
        }
    }
};

Mat operator*(const Mat &a, const Mat &b) {
    Mat c;
    for(int k = 0; k < all; k++) {
        for(int i = 0; i < all; i++) {
            for(int j = 0; j < all; j++) {
                c.val[i][j] = (c.val[i][j] + a.val[i][k] * b.val[k][j]) % MOD;
            }
        }
    }
    return c;
}

bool check(int mask1, int mask2) {
    for(int i = 0; i < m - 1; i++) {
        int ul = mask1 >> i & 1;
        int ur = mask1 >> i >> 1 & 1;
        int dl = mask2 >> i & 1;
        int dr = mask2 >> i >> 1 & 1;
        int sum = ul + ur + dl + dr;
        if(sum == 0 || sum == 4) return false;
    }
    return true;
}

bool isZero() {
    return len == -1;
}

bool mod2() {
    return row[0] & 1;
}

void updateLen(int &len) {
    for(int i = len; i >= 0; i--) {
        if(row[i] > 0) {
            len = i;
            return;
        }
    }
    len = -1;
}
void div2() {
    for(int i = len; i >= 0; i--) {
        if(i > 0) row[i-1] += (row[i] % 2) * 10; 
        row[i] /= 2;
    }
    updateLen(len);
}

void dec() {
    row[0]--;
    for(int i = 0; i < len; i++) {
        if(row[i] < 0) {
            row[i] += 10;
            row[i+1]--;
        } else break;
    }
    updateLen(len);
}

int main() {
    string s;
    while(cin >> s >> m >> MOD) {
        all = 1 << m;
        len = s.length() - 1;
        reverse(s.begin(), s.end());
        for(int i = 0; i <= len; i++) {
            row[i] = s[i] - '0';
        }
        dec();
        Mat a, b, c;
        for(int i = 0; i < all; i++)
            for(int j = 0; j < all; j++)
                if(check(i, j)) b.val[i][j]++;

        c.unit();
        while(!isZero()) {
            if(mod2()) {
                c = c * b;
            }
            b = b * b;
            div2();
        }
        for(int i = 0; i < all; i++) {
            a.val[0][i] = 1;
        }
        a = a * c;
        int ans = 0;
        for(int i = 0; i < all; i++) {
            ans += a.val[0][i];
        }
        cout << ans % MOD << endl;
    }
    return 0;
}
