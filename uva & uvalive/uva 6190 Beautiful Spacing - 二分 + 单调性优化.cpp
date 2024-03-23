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

const int N = 55555;
int n, m;
int w[N], sum[N];
bool visit[N];

bool check(int n, int m, int limit) {
    memset(visit, false, sizeof(visit));
    int le = 0, ri = 0;
    visit[0] = true;
    for (int i = 0; i <= n; i++) {
        if (!visit[i]) continue;
        if (sum[n] - sum[i] + n - i - 1 <= m) return true;
        while (ri <= n && sum[ri] - sum[i] + ri - i - 1 <= m) ri++;
        while (sum[le] - sum[i] + (le - i - 1) * limit < m) le++;
        while (le < ri) visit[le++] = true;
    }
    return false;
}

int main() {
    while (~scanf("%d%d", &m, &n), n + m) {
        sum[0] = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &w[i]), sum[i] = sum[i - 1] + w[i];
        int l = 1, r = m;
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            //cout << mid << " " << check(n, m, mid) << endl;
            if (check(n, m, mid)) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
