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
ll a[N];
//按位高斯消元，消元的时候必须从高位开始
void guass(int row, int col) {
    int r, c, i, j;
    for(c = col - 1, r = 0; r < row && c >= 0; r++, c--) {
        for(i = r; i < row; i++)
            if(a[i] >> c & 1) break;
        if(i == row) {
            r--;
            continue;
        }
        if(i != r) swap(a[i], a[r]);
        for(i = 0; i < row; i++) {
            if(i != r && (a[i] >> c & 1)) a[i] ^= a[r];
        }
    }
}

int main() {
    int n;
    while(cin >> n) {
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        guass(n, 60);
        sort(a, a + n);
        n = unique(a, a + n) - a;
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            ans ^= a[i];
        }
        cout << ans << endl;
    }
    return 0;
}
