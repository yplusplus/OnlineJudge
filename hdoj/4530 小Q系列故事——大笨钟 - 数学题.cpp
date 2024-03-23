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
int x, q;
int main() {
    int T, op, t;
    cin >> T;
    while (T--) {
        cin >> x >> q;
        while (q--) {
            scanf("%d", &op);
            scanf("%d", &t);
            if (op == 1) {
                printf("%.2f\n", 1.0 * t * (60.0 - x));
            } else if (op == 2) {
                printf("%.2f\n", 60.0 * 60 * t / (60.0 - x));
            } else {
                printf("%.2f\n", 43200.0 * t * 60.0 / x);
            }
        }
    }
    return 0;
}
