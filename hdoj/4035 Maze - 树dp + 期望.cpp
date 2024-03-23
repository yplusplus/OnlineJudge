#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
#include "cmath"
using namespace std;
#define pb push_back
#define maxn 10050
#define eps 1e-10
vector<int> g[maxn];
double k[maxn], e[maxn], p[maxn];
double a[maxn], b[maxn], c[maxn];
int n;

void dfs(int u, int fa) {
    int size = g[u].size();
    if(size == 1 && fa != -1) {
        a[u] = k[u];
        b[u] = c[u] = p[u];
        return;
    }
    double aa = 0, bb = 0, cc = 0;
    for(int i = 0; i < size; i++) {
        int v = g[u][i];
        if(v == fa) continue;
        dfs(v, u);
        aa += a[v], bb += b[v], cc += c[v];
    }
    double tmp = (1 - p[u] * bb / size);
    a[u] = (k[u] + p[u] * aa / size) / tmp;
    b[u] = (p[u] / size) / tmp;
    c[u] = (p[u] + p[u] * cc / size) / tmp;
    return;
}


int main() {
    int T, Case = 1;
    int u, v;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < maxn; i++) g[i].clear();
        for(int i = 0; i < n - 1; i++) {
            scanf("%d%d:", &u, &v);
            g[u].pb(v);
            g[v].pb(u);
        }
        for(int i = 1; i <= n; i++) {
            scanf("%lf%lf", &k[i], &e[i]);
            k[i] /= 100, e[i] /= 100;
            p[i] = 1 - k[i] - e[i];
        }
        dfs(1, -1);
        printf("Case %d: ", Case++);
        if(fabs(1 - a[1]) < eps) printf("impossible\n");
        else {
            double ans = c[1] / (1 - a[1]);
            printf("%.6f\n", ans);
        }
    }
    return 0;
}
