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

const int N = 10000;
const int MOD = 10000;
class BigInt {
    public:
        int a[N], len;
        BigInt() {
            memset(a, 0, sizeof(a));
            a[0] = 1;
            len = 0;
        }
        void operator*=(const int d) {
            for (int i = 0; i <= len; i++) {
                a[i] *= d;
            }
            for (int i = 0; i < N - 1; i++) {
                a[i + 1] += a[i] / MOD;
                a[i] %= MOD;
            }
            for (int i = N - 1; i >= 0; i--) {
                if (a[i]) {
                    len = i;
                    break;
                }
            }
        }
        void output() {
            printf("%d", a[len]);
            for (int i = len - 1; i >= 0; i--) {
                printf("%04d", a[i]);
            }
            puts("");
        }
};

int main() {
    int n;
    while (~scanf("%d", &n)) {
        if (!n) puts("1");
        else {
            BigInt t;
            for (int i = 2; i <= n; i++) {
                t *= i;
            }
            t.output();
        }
    }
    return 0;
}
