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

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int theFirstDay[13] = {0, 1, 4, 4, 7, 2, 5, 7, 3, 6, 1, 4, 6};
int n, m;

int calc(int n, int m) {
    if(m < 1 || m > 12) return -1;
    if(n < 1 || n > days[m]) return -1;
    int curDay = theFirstDay[m] + n - 1;
    while(curDay > 7) curDay -= 7;
    return curDay;
}
int main() {
    while(cin >> n >> m) {
        int ans = calc(n, m);
        if(ans == -1) puts("Impossible");
        else cout << ans << endl;
    }
    return 0;
}
