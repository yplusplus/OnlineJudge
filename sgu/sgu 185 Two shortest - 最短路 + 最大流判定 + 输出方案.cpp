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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 410
int maz[maxn][maxn];
int ds[maxn], dt[maxn], dist[maxn];
int n, m, s, t;
bool visit[maxn];
int path[maxn], pn;
int cap[maxn][maxn], flow[maxn][maxn];
void spfa(int s, int dist[]) {
    memset(visit, 0, sizeof(visit));
    for(int i = 0; i < maxn; i++) dist[i] = inf;
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    visit[s] = 1;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = 0;
        for(int i = 1; i <= n; i++) {
            if(dist[i] > dist[u] + maz[u][i]) {
                dist[i] = dist[u] + maz[u][i];
                if(!visit[i]) {
                    que.push(i);
                    visit[i] = 1;
                }
            }
        }
    }
}

bool bfs() {
    memset(dist, -1, sizeof(dist));
    int que[maxn];
    int head = 0, tail = 0;
    dist[t] = 0;
    que[tail++] = t;
    while(head < tail && dist[s] == -1) {
        int u = que[head++];
        for(int i = 0; i <= n; i++) {
            if(cap[i][u] > flow[i][u] && dist[i] == -1) {
                dist[i] = dist[u] + 1;
                que[tail++] = i;
            }
        }
    }
    return dist[s] != -1;
}

int dfs(int u, int d) {
    if(u == t) return d;
    int l = d;
    for(int i = 0; i <= n; i++) {
        if(cap[u][i] > flow[u][i] && dist[u] == dist[i] + 1) {
            int tmp = dfs(i, min(cap[u][i] - flow[u][i], l));
            flow[u][i] += tmp;
            flow[i][u] -= tmp;
            l -= tmp;
            if(l == 0) break;
        }
    }
    return d - l;
}

int Dinic() {
    int maxflow = 0;
    while(bfs()) {
        maxflow += dfs(s, inf);
    }
    return maxflow;
}

void dfs_path(int u) {
    path[pn++] = u;
    for(int i = 0; i <= n; i++) {
        if(flow[u][i] > 0) {
            flow[u][i]--;
            dfs_path(i);
            return;
        }
    }
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 0; i < maxn; i++)
            for(int j = 0; j < maxn; j++)
                maz[i][j] = inf;
        s = 0, t = n;
        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            maz[a][b] = maz[b][a] = c;
        }
        spfa(1, ds);
        spfa(n, dt);
        memset(cap, 0, sizeof(cap));
        memset(flow, 0, sizeof(flow));
        cap[s][1] = 2;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(ds[i] + maz[i][j] + dt[j] == ds[t]) {
                    cap[i][j] = 1;
                }
            }
        }
        int ans = Dinic();
        if(ans < 2) puts("No solution");
        else {
            pn = 0;
            dfs_path(s);
            for(int i = 1; i < pn; i++) printf("%d ", path[i]);
            printf("\n");
            pn = 0;
            dfs_path(s);
            for(int i = 1; i < pn; i++) printf("%d ", path[i]);
            printf("\n");
        }
    }
    return 0;
}
