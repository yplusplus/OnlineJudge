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

const int N = 6;
int a[N], b[N];
int n, m;
int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) {
            a[i] = 100, b[i] = 0;
        }
        while (m--) {
            int s, t;
            cin >> s >> t;
            s--, t--;
            if (a[s] <= 0) continue;
            if (a[t] > 0) b[s] += 3;
            a[t] -= 8;
        }
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
            if (a[i] < 0) a[i] = 0;
            cout << a[i] / 2 + b[i] << endl;
        }
    }
    return 0;
}
