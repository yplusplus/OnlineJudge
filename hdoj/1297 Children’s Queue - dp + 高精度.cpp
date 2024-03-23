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
const int N = 1111;
const int M = 555;
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
};
int n;
BigInt dp[N][3];
int main() {
    dp[1][1].setOne();
    dp[1][0].setOne();
    for (int i = 2; i < N; i++) {
        dp[i][0] = dp[i-1][2] + dp[i-1][0];
        dp[i][1] = dp[i-1][0];
        dp[i][2] = dp[i-1][1] + dp[i-1][2];
    }
    while (cin >> n) {
        BigInt ans = dp[n][0] + dp[n][2];
        for (int i = ans.len - 1; i >= 0; i--) {
            putchar('0' + ans.digit[i]);
        }
        puts("");
    }
    return 0;
}
