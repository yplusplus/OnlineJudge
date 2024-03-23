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
    int n;
    while(cin >> n) {
        if(n <= 8) cout << 0 << endl;
        else if(n == 9) cout << 8 << endl;
        else {
            printf("72");
            for(int i = 11; i <= n; i++) printf("0");
            puts("");
        }
    }
    return 0;
}

/*
1111111111
1119357639
1380642361
1388888889
1611111111
1619357639
1880642361
1888888889
2111111111
2119357639
2380642361
2388888889
2611111111
2619357639
2880642361
2888888889
*/
