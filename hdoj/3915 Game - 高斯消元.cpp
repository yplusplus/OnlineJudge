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

const int N = 111;
int a[N];
int n;
int gauss(int row, int col) {
    int i, j, r, c;
    for (r = c = 0; r < row && c < col; r++, c++) {
        for (i = r; i < row; i++) {
            if (a[i] >> c & 1) break;
        }
        if (i == row) { r--; continue; }
        if (i != r) swap(a[i], a[r]);
        for (int i = r + 1; i < row; i++) {
            if (a[i] >> c & 1) a[i] ^= a[r];
        }
    }
    return row - r;
}

const int MOD = 1000007;
int fac[N];
int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1]  * 2 % MOD;
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        cout << fac[gauss(n, 32)] << endl;
    }
    return 0;
}
