#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 30;
int n;

void solve() {
    int a = inf, b;
    for(int i = 1; i * i <= n; i++) {
        if(n % i == 0 && (i + n / i) % 2 == 0) {
            if(a > (n / i - i) / 2) {
                a = (n / i - i) / 2;
                b = (n / i + i) / 2;
            }
        }
    }
    if(a == inf) cout << "IMPOSSIBLE" << endl;
    else cout << a << " " << b << endl;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        solve();
    }
    return 0;
}
