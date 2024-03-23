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
const int inf = 1 << 30;
#define maxn 150
int maz[maxn][maxn], path[maxn][maxn];
bool visit[maxn];
int dist[maxn], pre[maxn], stack[maxn];
int n, m;

void init() {
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++) 
            maz[i][j] = inf, path[i][j] = 0;
}

int Prim(int s) {
    for (int i = 1; i <= n; i++) dist[i] = maz[s][i], visit[i] = 0, pre[i] = s;
    int top = 0, sum = 0;
    visit[s] = true, dist[s] = 0, stack[top++] = s;
    while (1) {
        int u = -1;
        for (int i = 1; i <= n; i++)
            if (!visit[i] && (u == -1 || dist[u] > dist[i]))
                u = i;
        if (u == -1) break;
        sum += dist[u], stack[top++] = u, visit[u] = true;
        for (int i = 0; i < top; i++) {
            if (stack[i] == u) continue;
            path[stack[i]][u] = max(path[pre[u]][stack[i]], dist[u]);
            path[u][stack[i]] = path[stack[i]][u];
        }
        for (int i = 1; i <= n; i++)
            if (!visit[i] && (maz[u][i] < dist[i]))
                dist[i] = maz[u][i], pre[i] = u;
    }
    return sum;
}

void SMT() {//次小生成树
    int Min = inf, sum = Prim(1);//先求一次最小生成树
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            if (pre[i] != j && pre[j] != i && maz[i][j] < inf)
                Min = min(Min, sum - path[i][j] + maz[i][j]);
    if (Min == sum) puts("Not Unique!");
    else printf("%d\n", sum);
}

int main() {
    int T, u, v, w;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            maz[u][v] = maz[v][u] = w;
        }
        SMT();
    }
    return 0;
}
