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
const int N = 111111;
const ll mod = 1000000007LL;
ll a[N], b[N], c[N];
ll sumA[N], sumB[N];
int n;
int main() {
    while(~scanf("%d", &n)) {
        sumA[0] = sumB[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            a[i] %= mod;
            sumA[i] = (sumA[i-1] + a[i]) % mod;
        }
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &b[i]);
            b[i] %= mod;
            sumB[i] = (sumB[i-1] + b[i]) % mod;
        }
        memset(c, 0, sizeof(c));
        for(int i = 1; i <= n; i++) {
            c[i] = (c[i] + a[i] * b[i] % mod) % mod;
            c[i] = (c[i] + a[i] * sumB[i-1] % mod) % mod;
            c[i] = (c[i] + b[i] * sumA[i-1] % mod) % mod;
            printf("%lld", c[i]);
            printf("%c", i == n ? '\n' : ' ');
        }
    }
    return 0;
}
