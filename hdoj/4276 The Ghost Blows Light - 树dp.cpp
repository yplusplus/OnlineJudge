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
#define maxn 110
int val[maxn];
int dp[maxn][550];
int f[550];
int pre[maxn];
int n, t;
bool visit[maxn];
int eh[maxn], tot;
int q[maxn], qn;
struct Edge {
    int u, v, w, next;
}et[maxn*maxn];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int w) {
    Edge e = {u, v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

int bfs(int s) {
    memset(pre, -1, sizeof(pre));
    memset(visit, false, sizeof(visit));
    queue<int> que;
    que.push(s);
    que.push(0);
    visit[s] = 1;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        int ti = que.front(); que.pop();
        if(u == n) return ti;
        for(int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, w = et[i].w;
            if(visit[v]) continue;
            pre[v] = u;
            visit[v] = 1;
            que.push(v);
            que.push(ti + w);
        }
    }
}

void dfs(int u) {
    visit[u] = true;
    for(int i = 0; i <= t; i++) dp[u][i] = val[u];
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v, w = et[i].w;
        if(visit[v]) continue;
        dfs(v);
        for(int j = t; j >= 0; j--)
            for(int k = 0; k <= j; k++)
                if(j - k - 2 * w >= 0) dp[u][j] = max(dp[u][j], dp[u][j-k-2*w] + dp[v][k]);
    }
}

int main() {
    while(~scanf("%d%d", &n, &t)) {
        init();
        for(int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            addedge(a, b, c);
            addedge(b, a, c);
        }
        for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
        int ti = bfs(1);
        if(ti > t) puts("Human beings die in pursuit of wealth, and birds die in pursuit of food!");
        else {
            t -= ti;
            int x = n;
            qn = 0;
            memset(visit, false, sizeof(visit));
            while(x != -1) {
                visit[x] = true;
                q[qn++] = x;
                x = pre[x];
            }
            memset(f, 0, sizeof(f));
            for(int k = 0; k < qn; k++) {
                dfs(q[k]);
                for(int i = t; i >= 0; i--)
                    for(int j = 0; j <= i; j++)
                        f[i] = max(f[i], f[i-j] + dp[q[k]][j]);
            }
            int res = *max_element(f, f + t + 1);
            printf("%d\n", res);
        }
    }
    return 0;
}
