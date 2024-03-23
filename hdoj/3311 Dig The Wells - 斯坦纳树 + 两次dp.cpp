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
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 1050
const int inf = 1 << 29;
struct Edge {
    int v, w;
    Edge(){}
    Edge(int _v, int _w) {
        v = _v, w = _w;
    }
};
int n, m, p;
int dp[maxn][1<<5], minn[1<<5];
int val[maxn], hash[maxn];
bool visit[maxn][1<<5];
vector<Edge> vec[maxn];
queue<int> que;
void update(int cost, int v, int nst) {
    if(cost < dp[v][nst]) {
        dp[v][nst] = cost;
        if(!visit[v][nst]) {
            que.push(v + (nst << 10));
            visit[v][nst] = true;
        }
    }
}

void solve() {
    while(!que.empty()) que.pop();
    memset(hash, 0, sizeof(hash));
    memset(visit, false, sizeof(visit));
    int nn = 1 << n;
    for(int i = 0; i <= n + m; i++)
        for(int j = 0; j < nn; j++)
            dp[i][j] = inf;
    for(int i = 1; i <= n; i++) {
        hash[i] = 1 << (i - 1);
        update(val[i], i, hash[i]);
    }
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        int u = now % (1 << 10), st = now >> 10;
        visit[u][st] = false;
        int size = vec[u].size();
        for(int i = 0; i < size; i++) {
            int v = vec[u][i].v, w = vec[u][i].w;
            update(dp[u][st] + w - val[u] + val[v], v, st | hash[v]);
        }
        int t = nn - 1 - st;
        for(int i = t; i; i = (i - 1) & t) {
            update(dp[u][st] + dp[u][i|hash[u]] - val[u], u, st | i);
        }
    }
    for(int i = 0; i < nn; i++) {
        minn[i] = inf;
        for(int j = 0; j <= n + m; j++)
            minn[i] = min(minn[i], dp[j][i]);
    }
    for(int i = 0; i < nn; i++)
        for(int j = i; j; j = (j - 1) & i)
            minn[i] = min(minn[i], minn[i-j] + minn[j]);
    printf("%d\n", minn[nn-1]);
}

int main() {
    while(~scanf("%d%d%d", &n, &m, &p)) {
        for(int i = 0; i < maxn; i++) vec[i].clear();
        for(int i = 1; i <= n + m; i++) scanf("%d", &val[i]);
        for(int i = 0; i < p; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            vec[u].pb(Edge(v, w));
            vec[v].pb(Edge(u, w));
        }
        solve();
    }
    return 0;
}
