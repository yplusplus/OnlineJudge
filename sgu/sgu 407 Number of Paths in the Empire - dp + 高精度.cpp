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
const int L = 7777;
int n, m;
//dp
//dp[0][i] 表示经过了i条边现在在0号点
//dp[1][i] 表示经过了i条边现在在非0号点
//dp[0][i] = dp[1][i-1];
//dp[1][i] = dp[0][i-1] * n + dp[1][i-1] * 2;
//要高精度，自己随手写了一个
//如果TLE的话，可以利用矩阵优化！！
//怕MLE，用了滚动数组

struct BigInt {
    int num[L];
    int length;
    BigInt() {
        memset(num, 0, sizeof(num));
        length = 0;
    }
    BigInt(const int c) {
        memset(num, 0, sizeof(num));
        length = 0;
        num[0] = c;
    }
    bool isZero() {
        return length == 0 && num[0] == 0;
    }
    BigInt operator *(const int c) {
        BigInt result = BigInt();
        for(int i = 0; i < L; i++) {
            result.num[i] = num[i] * c;
        }
        for(int i = 0; i < L; i++) {
            if(result.num[i] >= 10) {
                result.num[i+1] += result.num[i] / 10;
                result.num[i] %= 10;
            }
        }
        result.updateLength();
        return result;
    }
    BigInt operator +(const BigInt &a) {
        BigInt result = BigInt();
        for(int i = 0; i < L; i++) {
            result.num[i] += num[i] + a.num[i];
            if(result.num[i] >= 10) {
                result.num[i+1] += result.num[i] / 10;
                result.num[i] %= 10;
            }
        }
        result.updateLength();
        return result;
    }
    void updateLength() {
        length = 0;
        for(int i = L - 1; i >= 0; i--) {
            if(num[i]) {
                length = i;
                return;
            }
        }
    }
    void print() {
        for(int i = length; i >= 0; i--) {
            putchar(num[i] + '0');
        }
        puts("");
    }
}dp[2][2];

int main() {
    while(cin >> n >> m) {
        dp[0][0] = BigInt(1);
        dp[1][0] = BigInt(0);
        for(int i = 1; i <= m; i++) {
            dp[0][i & 1] = dp[1][(i-1) & 1];
            dp[1][i & 1] = (dp[0][(i-1) & 1] * n) + (dp[1][(i-1) & 1] * 2);
        }
        dp[0][m&1].print();
    }
    return 0;
}
