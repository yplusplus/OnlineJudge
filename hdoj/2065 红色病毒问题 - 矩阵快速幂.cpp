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

ull n;
const int MOD = 100;
const int N = 4;
struct Mat {
    int val[N][N];
    Mat(){};
    void zero() {
        memset(val, 0, sizeof(val));
    }
    void unit() {
        zero();
        for (int i = 0; i < N; i++) val[i][i] = 1;
    }
    Mat operator+(const Mat &x) const {
        Mat res;
        res.zero();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                res.val[i][j] = (val[i][j] + x.val[i][j]) % MOD;
            }
        }
        return res;
    }
    Mat operator*(const Mat &x) const {
        Mat res;
        res.zero();
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                if (!val[i][k]) continue;
                for (int j = 0; j < N; j++) {
                    res.val[i][j] += val[i][k] * x.val[k][j];
                    if (res.val[i][j] >= MOD) res.val[i][j] %= MOD;
                }
            }
        }
        return res;
    }
    Mat operator^(int n) {
        Mat res;
        Mat tmp = *this;
        res.unit();
        while (n) {
            if (n & 1) res = res * tmp;
            tmp = tmp * tmp;
            n >>= 1;
        }
        return res;
    }
};

Mat c[64];
const int val[N][N] = {2, 1, 1, 0, 1, 2, 0, 1, 1, 0, 2, 1, 0, 1, 1, 2};

int main() {
    memcpy(c[0].val, val, sizeof(val));
    for (int i = 1; i < 64; i++) {
        c[i] = c[i - 1] * c[i - 1];
    }
    int T;
    while (~scanf("%d", &T), T) {
        int Case = 1;
        while (T--) {
            cin >> n;
            Mat ans;
            ans.zero();
            ans.val[0][0] = 1;
            int cnt = 0;
            while (n) {
                if (n & 1) ans = ans * c[cnt];
                cnt++, n >>= 1;
            }
            printf("Case %d: %d\n", Case++, ans.val[0][0]);
        }
        puts("");
    }
    return 0;
}
