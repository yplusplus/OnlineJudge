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
int a[N], cnt[N];
int n;

//greedy
//单独考虑每个点
//求出经过点i的最小单车数，然后两两合并相邻点的单车数量

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        memset(a, 0, sizeof(a));
        memset(cnt, 0, sizeof(cnt));
        scanf("%d", &n);
        int sum = 0, ans = 0;
        for (int i = 1; i < n; i++) {
            int b, c, d;
            scanf("%d%d%d", &b, &c, &d);
            sum += d;
            cnt[b] += d;
            cnt[c] += d;
            a[b] = max(a[b], d);
            a[c] = max(a[c], d);
        }
        for (int i = 1; i <= n; i++) {
            if (a[i] * 2 >= cnt[i]) ans += a[i];
            else ans += (cnt[i] + 1) >> 1;
        }
        ans -= sum;
        printf("Case #%d: %d\n", Case++, ans);
    }
    return 0;
}
