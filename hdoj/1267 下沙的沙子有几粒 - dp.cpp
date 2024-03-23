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
const int N = 22;
ll dp[N][N];
int main() {
    for (int i = 0; i < N; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    int n, m;
    while (cin >> n >> m) {
        cout << dp[n][m] << endl;
    }
    return 0;
}
