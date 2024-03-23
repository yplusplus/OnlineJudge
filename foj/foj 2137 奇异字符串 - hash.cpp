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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111111;
const int M = 26;
char str[N];
vector<int> alpha[M];
const int MOD = 15485863;
const int h1 = 131;
const int h2 = 29;
int len;
int fac1[N], fac2[N];
int sum1[N], sum2[N];

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    return (1LL * a * b) % MOD;
}

ll sqr(ll x) { return x * x; }

bool check(int x1, int y1, int x2, int y2, int sum[], int fac[]) {
    int t1 = (sum[y1] + MOD - sum[x1 - 1]) % MOD;
    int t2 = (sum[y2] + MOD - sum[x2 - 1]) % MOD;
    t1 = mul(t1, fac[len + 1 - x1]);
    t2 = mul(t2, fac[len + 1 - x2]);
    return t1 == t2;
}

int main() {
    fac1[0] = fac2[0] = 1;
    for (int i = 1; i < N; i++) { fac1[i] = mul(fac1[i - 1], h1); fac2[i] = mul(fac2[i - 1], h2); }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", str + 1);
        for (int i = 0; i < M; i++) {
            alpha[i].clear();
            alpha[i].pb(0);
        }
        len = strlen(str + 1);
        sum1[0] = 0;
        for (int i = 1; i <= len; i++) {
            sum1[i] = add(sum1[i - 1], mul(str[i] - 'a' + 1, fac1[i]));
            sum2[i] = add(sum2[i - 1], mul(str[i] - 'a' + 1, fac2[i]));
            alpha[str[i] - 'a'].pb(i);
        }
        for (int i = 0; i < M; i++) {
            alpha[i].pb(len + 1);
        }
        ll ans = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 1; j < alpha[i].size() - 1; j++) {
                int t = min(alpha[i][j] - alpha[i][j - 1], alpha[i][j + 1] - alpha[i][j]) - 1;
                for (int k = 1; k <= t; k++) {
                    if (check(alpha[i][j] - k, alpha[i][j] - 1, alpha[i][j] + 1, alpha[i][j] + k, sum1, fac1)
                    && check(alpha[i][j] - k, alpha[i][j] - 1, alpha[i][j] + 1, alpha[i][j] + k, sum2, fac2)) {
                        ans += sqr(2 * k + 1);
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
