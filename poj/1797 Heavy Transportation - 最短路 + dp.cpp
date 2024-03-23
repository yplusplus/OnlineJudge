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
const int inf = 1 << 30;
int n, m;
int maz[maxn][maxn];
int dist[maxn];
bool visit[maxn];
void prim(int s) {
    memset(visit, false, sizeof(visit));
    memset(dist, -1, sizeof(dist));
    dist[s] = inf;
    while(1) {
        int u = -1;
        for(int i = 1; i <= n; i++)
            if(!visit[i] && (u == -1 || dist[i] > dist[u])) 
                u = i;
        if(u == -1) break;
        visit[u] = true;
        for(int i = 1; i <= n; i++) {
            if(!visit[i] && maz[u][i] != -1)
                dist[i] = max(dist[i], min(dist[u], maz[u][i]));
        }
    }
}

int main() {
    int T, Case = 1;
    int u, v, w;
    scanf("%d", &T);
    while(T--) {
        memset(maz, -1, sizeof(maz));
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            maz[u][v] = maz[v][u] = w;
        }
        prim(1);
        printf("Scenario #%d:\n%d\n\n", Case++, dist[n]);
    }
    return 0;
}
