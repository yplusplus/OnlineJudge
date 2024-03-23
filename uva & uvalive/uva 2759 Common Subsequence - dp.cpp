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
const int N = 5555;
int dp[N][N];
char s[N], t[N];
int main() {
    while (~scanf("%s%s", s, t)) {
        int slen = strlen(s), tlen = strlen(t);
        for (int i = 0; i <= slen; i++) {
            for (int j = 0; j <= tlen; j++) {
                dp[i][j] = 0;
            }
        }
        for (int i = 0; i < slen; i++) {
            for (int j = 0; j < tlen; j++) {
                if (s[i] == t[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
                else {
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        }
        cout << dp[slen][tlen] << endl;
    }
    return 0;
}
