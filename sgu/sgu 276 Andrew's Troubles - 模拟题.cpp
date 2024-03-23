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

int s, p;
int main() {
    while(cin >> s >> p) {
        int ans;
        int delta = p - s;
        if(delta <= 0) ans = 0;
        else if(delta < 300) ans = 1;
        else if(delta < 900) ans = 2;
        else if(delta < 1800) ans = 3;
        else ans = 4;
        cout << ans << endl;
    }
    return 0;
}
