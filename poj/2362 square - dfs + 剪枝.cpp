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
int stick[N];
int sum, n;
bool visit[N];

bool dfs(int i, int cur, int target, int cnt) {
    //cout << i << " " << cur << " " << target << " " << cnt << endl;
    if (cnt == 4) {
        return true;
    }
    for (int j = i; j < n; j++) {
        if (visit[j]) continue;
        if (j && !visit[j - 1] && stick[j] == stick[j - 1]) continue;
        if (stick[j] + cur == target) {
            visit[j] = true;
            if (dfs(0, 0, target, cnt + 1)) return true;
            visit[j] = false;
        } else if (stick[j] + cur < target) {
            visit[j] = true;
            if (dfs(j + 1, cur + stick[j], target, cnt)) return true;
            visit[j] = false;
        }
        if (cur == 0) return false;
    }
    return false;
}

bool solve() {
    if (sum % 4) return false;
    memset(visit, false, sizeof(visit));
    return dfs(0, 0, sum / 4, 0);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> stick[i];
            //cout << stick[i] << endl;
            sum += stick[i];
        }
        sort(stick, stick + n, greater<int>());
        //for (int i = 0; i < n; i++) {
            //cout << stick[i] << endl;
        //}
        puts(solve() ? "yes" : "no");
    }
    return 0;
}
