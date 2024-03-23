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
const int N = 111111;
char s[N];
int n;
int mini( char ch[] ) {
    int i = 0, j = 1, k = 0, t;
    while (i < n && j < n && k < n) {
        t = ch[(i + k) % n] - ch[(j + k) % n];
        if (!t) k++;
        else {
            if (t > 0) i = i + k + 1;
            else j = j + k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    return min(i, j);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d%s", &n, s);
        cout << mini(s) << endl;
    }
    return 0;
}
