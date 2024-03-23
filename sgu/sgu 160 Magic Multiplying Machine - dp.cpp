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
const int M = 1111;
int a[N];
int n, m;
bool dp[N][M];
int pre[N][M];

//dp
//dp[i][j] 表示考虑完前i个数，当前score为j是否合法

int main() {
    while(cin >> n >> m) {
        for(int i = 1; i <= n; i++) cin >> a[i];
        memset(pre, -1, sizeof(pre));
        memset(dp, false, sizeof(dp));
        dp[0][1] = true;
        for(int i = 0; i < n; i++) {
            for(int j = 1; j < m; j++) {
                if(dp[i][j]) {
                    int tmp = j * a[i+1] % m;
                    dp[i+1][tmp] = true;
                    pre[i+1][tmp] = j;
                    dp[i+1][j] = true;
                    pre[i+1][j] = j;
                }
            }
        }
        int ans = 1;

        for(int i = 1; i < m; i++)
            if(dp[n][i]) ans = max(ans, i);
        cout << ans << endl;
        vector<int> scheme;
        int x = ans;
        for(int i = n; i >= 1; i--) {
            int tmp = pre[i][x];
            if(tmp == x) continue;
            scheme.pb(i);
            x = tmp;
        }
        reverse(scheme.begin(), scheme.end());
        for(int i = 0; i < scheme.size(); i++) {
            cout << scheme[i] << " ";
        }
        puts("");
    }
    return 0;
}
