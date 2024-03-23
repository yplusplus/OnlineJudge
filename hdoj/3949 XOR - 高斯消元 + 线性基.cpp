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
#define maxn 10050
int n;
ll a[maxn];

void gauss(int row, int col) {
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
            if(i != r && a[i] >> c & 1) a[i] ^= a[r];
        }
    }
    sort(a, a + n);
    n = unique(a, a + n) - a;
}

ll calc(int k) {
    ll ans = 0;
    int i = 0;
    if(a[0] == 0) {
        if(k == 1) return 0;
        k--, i++;
    }
    for(; i < n && k; i++) {
        if(k & 1) ans ^= a[i];
        k >>= 1;
    }
    return k ? -1 : ans;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        gauss(n, 64);
        printf("Case #%d:\n", Case++);
        int q, k;
        scanf("%d", &q);
        while(q--) {
            scanf("%d", &k);
            cout << calc(k) << endl;
        }
    }
    return 0;
}
