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

const int N = 22;
int a[N], b[N];
int sum, n, k;
bool visit[N];

bool dfs(int start, int cnt, int cur, int target) {
    if (cnt == k) {
        return true;
    }
    for (int i = start; i < n; i++) {
        if (visit[i]) continue;
        if (i && a[i] == a[i - 1] && !visit[i - 1]) continue;
        if (cur + a[i] == target) {
            visit[i] = true;
            if (dfs(0, cnt + 1, 0, b[cnt + 1])) return true;
            visit[i] = false;
        } else if (cur + a[i] < target) {
            visit[i] = true;
            if (dfs(i + 1, cnt, cur + a[i], target)) return true;
            visit[i] = false;
        }
        //if (cur == 0) return false;
    }
    return false;
}

int solve() {
    int d = 0;
    for (int d = 0; ; d++) {
        int tmpSum = 0;
        b[0] = 0;
        for (int i = 1; i < k; i++) {
            b[i] = b[i-1] + d;
            tmpSum += b[i];
        }
        if (sum - tmpSum < 0) break;
        if ((sum - tmpSum) % k) continue;
        for (int i = 0; i < k; i++) {
            b[i] += (sum - tmpSum) / k;
            //cout << b[i] << " ";
        }
        //cout << endl;
        memset(visit, false, sizeof(visit));
        //cout << d << endl;
        if (dfs(0, 0, 0, b[0])) return d;
        //cout << d << endl;
    }
    return -1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        sum = 0;
        for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];
        sort(a, a + n);
        reverse(a, a + n);
        int ans = solve();
        if (ans != -1) cout << ans << endl;
        else puts("Impossible");
    }
    return 0;
}
