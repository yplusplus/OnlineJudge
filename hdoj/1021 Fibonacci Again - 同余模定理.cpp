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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 1000050
int fib[maxn];
int main() {
    fib[0] = 7, fib[1] = 11;
    for(int i = 2; i < maxn; i++) {
        fib[i] = (fib[i-1] + fib[i-2]) % 3;
    }
    int n;
    while(~scanf("%d", &n)) {
        if(fib[n] == 0) puts("yes");
        else puts("no");
    }
    return 0;
}
