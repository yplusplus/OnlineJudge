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
    int n, m;
    while(cin >> m >> n) {
        if(n >= m) {
            for(int i = m; i <= n; i++) {
                if(i == n) printf("%d\n", i);
                else printf("%d ", i);
            }
        } else if(m % (n + 1) == 0) puts("none");
        else printf("%d\n", m % (n + 1));
    }
    return 0;
}
