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
const int N = 1111;
ll a[N];
int n;
//digit root[x] = (x + 8) % 9 + 1;
int main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 0; i < n; i++) cin >> a[i];
        if(a[0] == 0) cout << 0 << endl;
        else {
            int sum = 8;
            ll tmp = 1;
            for(int i = 0; i < n; i++) {
                tmp *= a[i];
                tmp %= 9LL;
                sum += tmp;
            }
            cout << sum % 9 + 1 << endl;
        }
    }
    return 0;
}
