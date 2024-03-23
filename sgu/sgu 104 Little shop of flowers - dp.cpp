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
const int F = 111;
const int V = 111;
int a[F][V];
int dp[F][V], pre[F][V];
int f, v;

int main() {
    while(cin >> f >> v) {
        for(int i = 1; i <= f; i++) {
            for(int j = 1; j <= v; j++) {
                cin >> a[i][j];
            }
        } 
        fill(&dp[0][0], &dp[F][V], -inf);
        memset(pre, -1, sizeof(pre));
        for(int j = 1; j <= v; j++) {
            dp[1][j] = a[1][j];
        }
        for(int i = 2; i <= f; i++) {
            for(int j = i; j <= v; j++) {
                int idx = 1;
                for(int k = 1; k < j; k++) {
                    if(dp[i-1][k] > dp[i-1][idx]) idx = k;
                }
                dp[i][j] = dp[i-1][idx] + a[i][j];
                pre[i][j] = idx;
            }
        }
        int ans = -inf;
        int idx = -1;
        for(int i = f; i <= v; i++)
            if(ans < dp[f][i]) ans = dp[f][idx = i];
        cout << ans << endl;
        vector<int> scheme;
        for(int i = f; i >= 1; i--) {
            scheme.pb(idx);
            idx = pre[i][idx];
        }
        sort(scheme.begin(), scheme.end());
        for(int i = 0; i < f; i++) {
            printf("%d%c", scheme[i], i == f - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
