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
const int N = 11;
int n, k;
int C[N][N];
int main() {
    C[0][0] = 1;
    for(int i = 1; i < N; i++) {
        C[i][i] = C[i][0] = 1;
        for(int j = 1; j < i; j++) {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
    while(cin >> n >> k) {
        int ans = 1;
        if(k > n) ans = 0;
        else {
            for(int i = 0; i < k; i++) {
                ans *= i + 1;
            }
            ans *= C[n][k] * C[n][k];
        }
        cout << ans << endl;
    }
    return 0;
}
