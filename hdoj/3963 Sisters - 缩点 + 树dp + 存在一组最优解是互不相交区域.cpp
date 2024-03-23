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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 1111;
const int M = 2222222;
int eh[N], tot, belong[N], bcc, dfn[N], low[N], Dindex;
int s[N], top;
int n, m, k;
int visit[N], cost[N];
int f[N], dist[N][N];
struct Edge {
    int u, v, next;
} et[M];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v) {
    Edge e = {u, v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void tarjan_dfs(int u, int pre) {
    dfn[u] = low[u] = ++Dindex, visit[u] = 1;
    s[++top] = u;
    int cnt = 0;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (v == pre && cnt == 0) { cnt++; continue; }
        if (!dfn[v]) {
            tarjan_dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                bcc++;
                while (1) {
                    belong[s[top]] = bcc;
                    cost[bcc]++;
                    if (s[top--] == v) break;
                }
            }
        } else if (visit[v]) { low[u] = min(low[u], dfn[v]); }
    }
    visit[u] = 0;
}

void tarjan() {
    top = bcc = Dindex = 0;
    memset(visit, 0, sizeof(visit));
    memset(dfn, 0, sizeof(dfn));
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan_dfs(i, 0);
        if (top) {
            bcc++;
            while (top) belong[s[top--]] = bcc, cost[bcc]++;
        }
    }
}

vector<int> vec[N];
void calculate_distance(int s, int u, int fa) {
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa) continue;
        dist[s][v] = dist[s][u] + 1;
        calculate_distance(s, v, u);
    }
}

void build() {
    for (int i = 0; i <= bcc; i++) vec[i].clear();
    for (int i = 0; i < tot; i += 2) {
        if (belong[et[i].u] != belong[et[i].v]) {
            //cout << belong[et[i].u] << " " << belong[et[i].v] << endl;
            vec[belong[et[i].u]].pb(belong[et[i].v]);
            vec[belong[et[i].v]].pb(belong[et[i].u]);
        }
    }
    n = bcc;
}

int dp[N][N];
void dfs(int u, int fa) {
    dp[u][0] = inf;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v != fa) dfs(v, u);
    }
    for (int j = 1; j <= n; j++) {
        dp[u][j] = f[dist[u][j]];
        for (int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i];
            if (v == fa) continue;
            dp[u][j] += min(dp[v][0], dp[v][j]);
        }
        if (dp[u][j] + k + cost[j] < dp[u][0]) {
            dp[u][0] = dp[u][j] + k + cost[j];
        }
    }
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &k)) {
        init();
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            addedge(a, b), addedge(b, a);
        }
        for (int i = 1; i < n; i++) scanf("%d", &f[i]);
        memset(cost, 0, sizeof(cost));
        tarjan();
        build();
        for (int i = 1; i <= n; i++) {
            dist[i][i] = 0;
            calculate_distance(i, i, 0);
        }
        dfs(1, 0);
        printf("%d\n", dp[1][0]);
    }
    return 0;
}
