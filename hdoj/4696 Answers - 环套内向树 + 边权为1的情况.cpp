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

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        int x;
        bool found = false;
        for (int i = 0; i < n; i++) scanf("%d", &x);
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            found |= (x & 1);
        }
        while (m--) {
            scanf("%d", &x);
            if (x <= 0 || ((x & 1) && !found)) puts("NO");
            else puts("YES");
        }
    }
    return 0;
}
