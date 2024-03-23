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

int a[110], n;
int main() {
    while(cin >> n, n) {
        int res = 0;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            res ^= a[i];
        }
        int ans = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] > (res ^ a[i])) ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
