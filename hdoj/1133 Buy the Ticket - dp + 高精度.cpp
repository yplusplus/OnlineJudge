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
const int M = 400;
class BigInt {
    public:
        int digit[M];
        int len;
        BigInt() {
            memset(digit, 0, sizeof(digit));
            len = 1;
        }
        void setOne() {
            digit[0] = 1;
            len = 1;
        }
        BigInt operator+(const BigInt &a) const {
            BigInt res;
            for (int i = 0; i < M - 1; i++) {
                res.digit[i] += digit[i] + a.digit[i];
                if (res.digit[i] >= 10) {
                    res.digit[i] -= 10;
                    res.digit[i+1]++;
                }
            }
            int newLen = M - 1;
            while (newLen >= 0 && !res.digit[newLen]) newLen--;
            res.len = max(newLen + 1, 1);
            return res;
        }
        BigInt operator*(const int &a) const {
            BigInt res;
            for (int i = 0; i < len; i++) {
                res.digit[i] = digit[i] * a;
            }
            for (int i = 0; i < M - 1; i++) {
                res.digit[i+1] += res.digit[i] / 10;
                res.digit[i] %= 10;
            }
            int newLen = M - 1;
            while (newLen >= 0 && !res.digit[newLen]) newLen--;
            res.len = max(newLen + 1, 1);
            return res;
        }
        BigInt operator*(const BigInt &a) const {
            BigInt res;
            for (int i = 0; i < a.len; i++) {
                for (int j = 0; j < len; j++) {
                    res.digit[i + j] += a.digit[i] * digit[j];
                }
            }
            for (int i = 0; i < M - 1; i++) {
                res.digit[i + 1] += res.digit[i] / 10;
                res.digit[i] %= 10;
            }
            int newLen = M - 1;
            while (newLen >= 0 && !res.digit[newLen]) newLen--;
            res.len = max(newLen + 1, 1);
            return res;
        }
        void output() {
            for (int i = len - 1; i >= 0; i--) {
                putchar(digit[i] + '0');
            }
            puts("");
        }
};

BigInt dp[N][N];
BigInt fac[N];

int main() {
    fac[0].setOne();
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i-1] * i;
    }
    for (int i = 0; i < N; i++) {
        dp[i][0].setOne();
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    int n, m;
    int Case = 1;
    while (cin >> n >> m, n + m) {
        printf("Test #%d:\n", Case++);
        (dp[n][m] * fac[n] * fac[m]).output();
    }
    return 0;
}
