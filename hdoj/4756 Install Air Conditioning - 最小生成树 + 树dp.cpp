#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
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
double maz[N][N];
bool visit[N];
double dist[N], dp[N][N];
int pre[N], n;
vector<int> vec[N];

double Prim(int s) {
    for (int i = 1; i <= n; i++) dist[i] = dinf, visit[i] = false;
    double sum = 0;
    dist[s] = 0;
    while (1) {
        int u = -1;
        for (int i = 1; i <= n; i++)
            if (!visit[i] && (u == -1 || dist[u] > dist[i]))
                u = i;
        if (u == -1) break;
        if (u != s) vec[u].pb(pre[u]), vec[pre[u]].pb(u);
        sum += dist[u], visit[u] = true;
        for (int i = 1; i <= n; i++)
            if (!visit[i] && (maz[u][i] < dist[i]))
                dist[i] = maz[u][i], pre[i] = u;
    }
    return sum;
}

struct Point {
    double x, y;
    void read() {
        scanf("%lf%lf", &x, &y);
    }
} point[N];

inline double sqr(double x) {
    return x * x;
}

double get_distance(const Point &a, const Point &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double dfs(int s, int u, int fa) {
    double ret = dinf;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa) continue;
        double t = dfs(s, v, u);
        dp[u][v] = min(dp[u][v], t);
        dp[v][u] = dp[u][v];
        ret = min(ret, t);
    }
    if (fa != s) ret = min(ret, maz[s][u]);
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        double k;
        scanf("%d%lf", &n, &k);
        for (int i = 1; i <= n; i++) point[i].read(), vec[i].clear();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                maz[i][j] = get_distance(point[i], point[j]);
                dp[i][j] = dinf;
            }
        }
        double cost = Prim(1);
        for (int i = 1; i <= n; i++) { dfs(i, i, 0); }
        double ans = cost;
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < vec[i].size(); j++) {
                int v = vec[i][j];
                if (v > 1) {
                    ans = max(ans, cost - maz[i][v] + dp[i][v]);
                }
            }
        }
        printf("%.2f\n", ans * k);
    }
    return 0;
}
