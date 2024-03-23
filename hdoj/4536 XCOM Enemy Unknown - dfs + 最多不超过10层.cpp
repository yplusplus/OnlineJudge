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
const int K = 111;
const int N = 20;
int n, m, k, ans;
int id[N], v[N], at[K][3];
bool check() {
    for (int i = 0; i < n; i++) {
        if (v[i] > 5) return false;
    }
    return true;
}

void dfs(int kk) {
    ans = max(ans, kk);
    if (kk >= k) return;
    for (int i = 0; i < 3; i++) {
        int tmp = v[at[kk][i]];
        v[at[kk][i]] -= 2;
        if (v[at[kk][i]] < 1) v[at[kk][i]] = 1;
        for (int t = 0; t < 3; t++) {
            if (t == i) continue;
            for (int j = 0; j < n; j++)
                if (id[j] == id[at[kk][t]]) {
                    v[j]++;
                }
            v[at[kk][t]]++;
        }
        if (check()) dfs(kk + 1);
        for (int t = 0; t < 3; t++) {
            if (t == i) continue;
            for (int j = 0; j < n; j++)
                if (id[j] == id[at[kk][t]]) v[j]--;
            v[at[kk][t]]--;
        }
        v[at[kk][i]] = tmp;
    }
}

int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) cin >> id[i];
        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = 0; i < k; i++)
            for (int j = 0; j < 3; j++)
                cin >> at[i][j];
        ans = 0;
        dfs(0);
        printf("Case #%d: %d\n", Case++, ans);
    }
    return 0;
}
