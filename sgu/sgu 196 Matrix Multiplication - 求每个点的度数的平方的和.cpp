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
const int N = 11111;
int degree[N];
int n, m;
//转化模型，实际上是求每个点的度数平方之和
int main() {
    while(cin >> n >> m) {
        memset(degree, 0, sizeof(degree));
        for(int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            degree[a]++, degree[b]++;
        }
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += 1LL * degree[i] * degree[i];
        }
        cout << ans << endl;
    }
    return 0;
}
