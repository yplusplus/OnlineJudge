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
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 1050
#define eps 1e-6

int n;
double d[maxn][maxn];
int cost[maxn][maxn];

struct Point {
    double x, y;
    int z;
}p[maxn];

double getdist(Point &a, Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int getcost(Point &a, Point &b) {
    return abs(a.z - b.z);
}

double prim(int s, double &l) {
    double anslen = 0.0, anscost = 0.0;
    bool visit[maxn];
    double dist[maxn], tmp, ans = 0.0;
    int pre[maxn];
    for(int i = 0; i < n; i++) visit[i] = false, dist[i] = 1e30;
    dist[s] = 0.0, pre[s] = s;
    while(1) {
        int u = -1;
        for(int i = 0; i < n; i++) {
            if(!visit[i] && (u == -1 || dist[i] < dist[u])) u = i;
        }
        if(u == -1) break;
        anscost += cost[pre[u]][u];
        anslen += d[pre[u]][u];
        ans += dist[u];
        visit[u] = true;
        for(int i = 0; i < n; i++) {
            if(!visit[i] && (tmp = 1.0 * cost[u][i] - l * d[u][i]) < dist[i])
                dist[i] = tmp, pre[i] = u;
        }
    }
    l = anscost / anslen;
    return ans;
}

void solve() {
    double ans= 0.0, tmp = 0.0;
    while(1) {
        double tmp = prim(0, ans);
        if(fabs(tmp) < eps) break;
    }
    printf("%.3f\n", ans);
}

int main() {
    while(scanf("%d", &n) && n) {
        for(int i = 0; i < n; i++) {
            scanf("%lf%lf%d", &p[i].x, &p[i].y, &p[i].z);
            for(int j = 0; j < i; j++) {
                d[i][j] = d[j][i] = getdist(p[i], p[j]);
                cost[i][j] = cost[j][i] = getcost(p[i], p[j]);
            }
        }
        solve();
    }
    return 0;
}
