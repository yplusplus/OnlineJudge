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
int profit[N], dp[N];
vector<int> vec[N];
int n;

//树dp
//dp[i] 表示以i为根的子树，取了i和剩下某些子孙的最大值

void dfs(int u, int fa) {
    dp[u] = profit[u];
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dfs(v, u);
        dp[u] += dp[v] > 0 ? dp[v] : 0;
    }
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> profit[i];
        vec[i].clear();
    }
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        vec[a].pb(b);
        vec[b].pb(a);
    }
    dfs(1, -1);
    cout << *max_element(dp + 1, dp + 1 + n) << endl;
    return 0;
}
