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
#define maxn 550
#define maxm 500000
const int inf = 1 << 28;
int maz[maxn][maxn];
int dp[maxn][maxn];
int rr[maxn], cc[maxn], mm[maxn];
int office[maxn];
int n, m;
int R, C, M;
int ans, anscost, eh[maxn], tot, low[maxn], p[maxn], dist[maxn]; 
int S, T; //源，汇
struct Edge {
    int u, v, cost, cap, flow, next; 
} et[maxm];
bool visit[maxn];

bool spfa() {
    queue<int> que;
    memset(visit, false, sizeof (visit));
    memset(p, -1, sizeof (p));
    memset(low, 0, sizeof(low));
    fill(&dist[0], &dist[maxn], inf);
    visit[S] = true, low[S] = inf, dist[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
            if (flow < cap && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                p[v] = i; //注意，这里是 i
                low[v] = min(low[u], cap - flow);
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dist[T] != inf;
}

void costflow() {
    ans = 0, anscost = 0;
    while (spfa()) {
        int x = p[T];
        ans += low[T];
        anscost += low[T] * dist[T];
        while (x != -1) {
            et[x].flow += low[T];
            et[x^1].flow -= low[T];
            et[x^1].cost = -et[x].cost;
            x = p[et[x].u];
        }
    }
}

void add(int u, int v, int cost, int cap, int flow) {
    Edge e = {u, v, cost, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap) {
    add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}

void init() {
    tot = 0;
    memset(eh, -1, sizeof (eh));
}

void floyd() {
    for(int k = 1; k <= n; k++) 
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
}

void solve() {
    init();
    floyd();
    int X = R + C + 1;
    S = 0, T = X + 1;
    for(int i = 1; i <= R; i++) addedge(S, i, 0, 1);
    for(int i = 1; i <= C; i++) addedge(R + i, T, 0, 1);
    addedge(X, T, 0, R - C);
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            for(int k = 1; k <= M; k++)
                dp[i][j] = min(dp[i][j], maz[rr[i]][cc[j]] + maz[cc[j]][mm[k]] + maz[mm[k]][office[i]]);
            if(dp[i][j] < inf) addedge(i, j + R, dp[i][j], 1);
        }
        addedge(i, X, maz[rr[i]][office[i]], 1);
    }
    costflow();
    double average = 1.0 * anscost / R;
    average = ceil(average);
    int aver = (int)average;
    int hh = 8 + aver / 60;
    int mins = aver % 60;
    printf("%02d:%02d\n", hh, mins);

}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                maz[i][j] = inf;
                dp[i][j] = inf;
            }
            maz[i][i] = 0;
        }
        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            maz[a][b] = maz[b][a] = c;
        }
        scanf("%d", &R);
        for(int i = 1; i <= R; i++) scanf("%d%d", &rr[i], &office[i]);
        scanf("%d", &C);
        for(int i = 1; i <= C; i++) scanf("%d", &cc[i]);
        scanf("%d", &M);
        for(int i = 1; i <= M; i++) scanf("%d", &mm[i]);
        solve();
    }
    return 0;
}
