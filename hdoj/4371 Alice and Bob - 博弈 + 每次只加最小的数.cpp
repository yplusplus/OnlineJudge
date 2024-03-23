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

int main() {
    int T, n, m, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        int a, b = inf;
        for(int i = 0; i < m; i++) {
            scanf("%d", &a);
            b = min(b, a);
        }
        n /= b;
        printf("Case #%d: ", Case++);
        if(n & 1) puts("Bob");
        else puts("Alice");
    }
    return 0;
}
