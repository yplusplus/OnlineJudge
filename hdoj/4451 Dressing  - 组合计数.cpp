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
const int N = 1111;
int n, m, k, p;
int cnt1[N], cnt2[N];

int main() {
    while (~scanf("%d%d%d", &n, &m, &k), n + m + k) {
        scanf("%d", &p);
        char s[20], t[20];
        int a, b;
        memset(cnt1, 0, sizeof(cnt1));
        memset(cnt2, 0, sizeof(cnt2));
        for (int i = 0; i < p; i++) {
            scanf("%s%d%s%d", s, &a, t, &b);
            if (s[0] == 'c') cnt1[b]++;
            else cnt2[a]++;
        }
        int ans = n * m * k;
        for (int i = 0; i <= m; i++) {
            ans -= cnt1[i] * k;
            ans -= cnt2[i] * n;
            ans += cnt1[i] * cnt2[i];
        }
        cout << ans << endl;
    }
    return 0;
}
