#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define eps 1e-10
int n;
double p[11][11];
double dp[1<<11];
string s[1<<11];

void solve() {
    int nn = 1 << n;
    dp[0] = 0.0;
    s[0] = "";
    for(int i = 1; i < nn; i++) {
        dp[i] = -1.0;
        for(int j = 0; j < n; j++) {
            if(i & (1 << j)) {
                double pp = 0.0;
                for(int k = 0; k < n; k++) {
                    if(i & (1 << k)) pp = max(pp, p[k][j]);
                }
                int m = i - (1 << j);
                double tmp = dp[m] + pp;
                if(dp[i] + eps < tmp || (dp[i] - eps < tmp && s[i] > s[m])) {//watashi判精度的方法，妙~
                    dp[i] = tmp;
                    char ch = j + 'A';
                    s[i] = s[m] + ch;
                }
            }
        }
    }
    printf("%.2f\n", dp[nn-1]);
    cout << s[nn-1] << endl;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cin >> p[i][j];
                p[i][j] /= 100.0;
            }
        }
        solve();
    }
    return 0;
}
