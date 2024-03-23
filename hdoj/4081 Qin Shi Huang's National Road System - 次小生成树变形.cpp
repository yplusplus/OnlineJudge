#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 1005
const double dinf = 1e10;
const int inf = 1 << 30;
int n, m;
int pre[maxn], stack[2*maxn], top;
double maz[maxn][maxn], dist[maxn], path[maxn][maxn];
bool visit[maxn];
struct Point {
    double x, y;
    int cnt;
}p[maxn];

double getdist(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double prim(int s) {
    double ans = 0;
    for(int i = 0; i < n; i++) visit[i] = false, dist[i] = dinf, pre[i] = s;
    dist[s] = 0, top = 0;
    while(1) {
        int u = -1;
        for(int i = 0; i < n; i++) {
            if(!visit[i] && (u == -1 || dist[i] < dist[u])) u = i;
        }
        if(u == -1) break;
        stack[top++] = u, visit[u] = true;
        ans += dist[u];
        for(int i = 0; i < top; i++) {
            if(stack[i] == u) continue;
            path[stack[i]][u] = max(path[stack[i]][pre[u]], dist[u]);
            path[u][stack[i]] = path[stack[i]][u];
        }
        for(int i = 0; i < n; i++) {
            if(!visit[i] && maz[u][i] < dist[i]) 
                dist[i] = maz[u][i], pre[i] = u;
        }
    }
    return ans;
}

void solve() {
    double MST = prim(0), ans = 0.0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            if((pre[i] == j || pre[j] == i)) ans = max(ans, (p[i].cnt + p[j].cnt) / (MST - maz[i][j]));
            else ans = max(ans, (p[i].cnt + p[j].cnt) / (MST - path[i][j]));
        }
    }
    printf("%.2f\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%lf%lf%d", &p[i].x, &p[i].y, &p[i].cnt);
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                maz[i][j] = getdist(p[i], p[j]);
                path[i][j] = 0.0;
            }
        }
        solve();
    }
    return 0;
}
