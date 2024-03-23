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
const int MOD = 1000000007;
int n, k, d;
int sum[1111][1111][11];
const int N = 1000;
const int D = 10;
void init() {
    memset(sum, 0, sizeof(sum));
    for(int i = 0; i <= N; i++)
        for(int j = 1; j <= D; j++)
            sum[i][0][j] = 1;
    for(int k = 1; k <= D; k++) {
        for(int i = 1; i <= N; i++) {
            sum[i][1][k] = sum[i-1][1][k] + 1;
        }
        for(int i = 2; i <= N; i++) {
            for(int j = 2; j <= N; j++) {
                if(i - k >= 0) sum[i][j][k] = (sum[i-1][j][k] + sum[i-k][j-1][k]) % MOD;
                else sum[i][j][k] = sum[i-1][j][k];
            }
        }
    }
}

int main() {
    int T, Case = 1;
    init();
    cin >> T;
    while (T--) {
        cin >> n >> k >> d;
        int ans = sum[n][k][d];
        for(int i = 1; i < d; i++) {
            for(int j = n; j > i - d + n; j--) {
                int tmp = j - i + 1 - 2 * d;
                if(j - i < d) continue;
                if(k - 2 == 0) {
                    ans = (ans - 1 + MOD) % MOD;
                } else if(tmp >= 0 && k - 2 >= 0) {
                    ans = (ans - sum[tmp][k-2][d] + MOD) % MOD;
                }
            }
        }
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}
