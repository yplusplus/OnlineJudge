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
#define maxn 510
#define maxm 1000000
bool maz[maxn][maxn];
int val[maxn];
int eh[maxn], tot, cur[maxn];
int dist[maxn];
int ans[maxn];
bool x[maxn];
int n, m, s, t, k;
struct Edge {
    int v, cap, flow, next;
}et[maxm];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
    Edge e = {v, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
    add(u, v, cap, 0), add(v, u, 0, 0);
}

bool bfs() {
    int que[maxn];
    int head = 0, tail = 0;
    memset(dist, -1, sizeof(dist));
    dist[s] = 0;
    que[tail++] = s;
    while(head < tail && dist[t] == -1) {
        int u = que[head++];
        for(int i = eh[u]; i != -1; i = et[i].next) {
            if(et[i].cap > et[i].flow && dist[et[i].v] == -1) {
                dist[et[i].v] = dist[u] + 1;
                que[tail++] = et[i].v;
            }
        }
    }
    return dist[t] != -1;
}

int dfs(int u, int d) {
    if(u == t) return d;
    int l = d;
    for(int &i = cur[u]; i != -1; i = et[i].next) {
        if(et[i].cap > et[i].flow && dist[u] + 1 == dist[et[i].v]) {
            int tmp = dfs(et[i].v, min(et[i].cap - et[i].flow, l));
            et[i].flow += tmp;
            et[i^1].flow -= tmp;
            l -= tmp;
            if(l == 0) break;
        }
    }
    return d - l;
}

int Dinic() {
    int flow = 0;
    while(bfs()) {
        for(int i = s; i <= t; i++) cur[i] = eh[i];
        flow += dfs(s, inf);
    }
    return flow;
}

void solve(int mm) {
    init();
    s = 0, t = n + 1;
    for(int i = 1; i <= n; i++) {
        if(x[i]) {
            int zero = 0, one = 0;
            for(int j = 1; j <= n; j++) {
                if(maz[i][j]) {
                    if(x[j]) addedge(i, j, 1);
                    else {
                        if(val[j] & mm) one++;
                        else zero++;
                    }
                }
            }
            addedge(s, i, one);
            addedge(i, t, zero);
        }
    }
    int flow = Dinic();
    for(int i = 1; i <= n; i++) {
        if(x[i]) {
            ans[i] |= (dist[i] == -1 ? 0 : mm);
        }
    }
}

int main() {
    int T;
    int a, b;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        memset(maz, 0, sizeof(maz));
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &a, &b);
            maz[a][b] = maz[b][a] = 1;
        }
        memset(x, true, sizeof(x));
        scanf("%d", &k);
        for(int i = 0; i < k; i++) {
            scanf("%d%d", &a, &b);
            val[a] = b;
            x[a] = false;
        }
        memset(ans, 0, sizeof(ans));
        for(int i = 0; i <= 30; i++) {
            solve(1 << i);
        }
        for(int i = 1; i <= n; i++) {
            printf("%d\n", x[i] ? ans[i] : val[i]);
        }
    }
    return 0;
}
