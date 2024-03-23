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
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 1111;
const int M = 55555;
int n, m;
int eh[N], tot;
int low[N], dist[N], pre[N];
bool visit[N];
struct Edge {
    int u, v, cost, cap, flow, next;
} et[M];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void add(int u, int v, int cost, int cap, int flow) {
    Edge e = {u, v, cost, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap) {
    add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}

bool spfa(int s, int t) {
    deque<int> que;
    //queue<int> que;
    for (int i = 0; i < N; i++) dist[i] = -inf;
    memset(visit, false, sizeof(visit));
    //memset(pre, -1, sizeof(pre));
    //memset(low, 0, sizeof(low));
    low[s] = inf, pre[s] = -1;
    dist[s] = 0;
    que.push_back(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop_front();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, cost = et[i].cost;
            if (et[i].cap - et[i].flow && dist[v] < dist[u] + cost) {
                dist[v] = dist[u] + cost;
                pre[v] = i;
                low[v] = min(low[u], et[i].cap - et[i].flow);
                if (!visit[v]) {
                    visit[v] = true;
                    if (!que.empty() && dist[v] <= dist[que.front()]) que.push_front(v);
                    else que.push_back(v);
                }
            }
        }
    }
    return dist[t] != -inf;
}

int flow, cost;
void mcmf(int s, int t) {
    flow = cost = 0;
    while (spfa(s, t)) {
        //cout << " " << endl;
        flow += low[t];
        cost += low[t] * dist[t];
        int x = pre[t];
        while (x != -1) {
            et[x].flow += low[t];
            et[x ^ 1].flow -= low[t];
            x = pre[et[x].u];
        }
    }
}

    
int c[N];
int main() {
    //freopen("zjoi13_defend.in", "r", stdin);
    //freopen("zjoi13_defend.out", "w", stdout);
    while (~scanf("%d%d", &n, &m)) {
        init();
        int s = 0, t = n + 2;
        for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
        c[0] = c[n + 1] = 0;
        for (int i = 1; i <= n + 1; i++) {
            int delta = c[i] - c[i - 1];
            if (delta > 0) addedge(s, i, 0, delta);
            else addedge(i, t, 0, -delta);
            if (i > 1) addedge(i - 1, i, 0, inf);
        }
        for (int i = 1; i <= m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            //addedge(a, b + 1, c, inf);
            addedge(a, b + 1, c, inf);
        }
        mcmf(s, t);
        printf("%d\n", cost);
    }
    return 0;
}
