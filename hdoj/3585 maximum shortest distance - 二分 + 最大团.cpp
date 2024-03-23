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
#define sq(x) (x) * (x)
const int inf = 1 << 29;
const double dinf = 1e300;
const ll linf = 1LL << 55;
#define maxn 60
#define eps 1e-6
pii p[maxn];
int dist[maxn][maxn];
bool g[maxn][maxn];
int dp[maxn], stk[maxn][maxn], mx;
int n, k;

void build(int mid) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(dist[i][j] >= mid) g[i][j] = 1;
            else g[i][j] = 0;
}

int dfs(int n, int ns, int dep) {
    if(ns == 0) {
        if(dep > mx) mx = dep;
        return 1;
    }
    for(int i = 0; i < ns; i++) {
        int k = stk[dep][i];
        int cnt = 0;
        if(dep + n - k <= mx) return 0;
        if(dep + dp[k] <= mx) return 0;
        for(int j = i + 1; j < ns; j++) {
            int p = stk[dep][j];
            if(g[k][p]) stk[dep+1][cnt++] = p;
        }
        dfs(n, cnt, dep + 1);
    }
    return 1;
}

int clique(int n) {
    mx = 0;
    int ns = 0;
    for(int i = n - 1; i >= 0; i--) {
        ns = 0;
        for(int j = i + 1; j < n; j++) {
            if(g[i][j]) stk[1][ns++] = j;
        }
        dfs(n, ns, 1);
        dp[i] = mx;
    }
    return mx;
}
int main() {
    while(~scanf("%d%d", &n, &k)) {
        for(int i = 0; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            p[i] = mp(x, y);
        }
        vector<int> vec;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = (p[i].fi - p[j].fi) * (p[i].fi - p[j].fi) + (p[i].se - p[j].se) * (p[i].se - p[j].se);
                vec.pb(dist[i][j]);
                //cout << dist[i][j] << endl;
            }
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()) , vec.end());
        int ans;
        int l = 0, r = vec.size() - 1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            build(vec[mid]);
            if(clique(n) >= k) {
                ans = mid;
                l = mid + 1;
            } else r = mid - 1;
        }
        printf("%.2f\n", sqrt(1.0 * vec[ans]));
    }
    return 0;
}
