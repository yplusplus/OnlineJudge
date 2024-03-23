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
const int N = 16666;
vector<int> vec[N];
int son[N], dp[N];
int n;
void dfs(int u, int fa) {
    int tmp = 0;
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dfs(v, u);
        son[u] += son[v];
        tmp = max(tmp, son[v]);
    }
    son[u]++;
    dp[u] = max(tmp, n - son[u]);
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) vec[i].clear();
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        vec[a].pb(b);
        vec[b].pb(a);
    }
    memset(son, 0, sizeof(son));
    dfs(1, -1);
    int ans = inf;
    vector<int> scheme;
    for(int i = 1; i <= n; i++) {
        if(dp[i] < ans) {
            scheme.clear();
            scheme.pb(i);
            ans = dp[i];
        } else if(dp[i] == ans) {
            scheme.pb(i);
        }
    }
    cout << ans << " " << scheme.size() << endl;
    for(int i = 0; i < scheme.size(); i++) {
        printf("%d%c", scheme[i], i == scheme.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
