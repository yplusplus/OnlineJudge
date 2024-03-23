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
#define maxm 100050
int id[100050];
int a[maxn], b[maxn], w[maxn];
int ans, anscost, eh[maxn], tot, low[maxn], p[maxn], dist[maxn]; 
int s, t; //源，汇
int n, k;
bool visit[maxn];
struct Edge {
    int u, v, cost, cap, flow, next; 
} et[maxm];
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
bool spfa() {
    queue<int> que;
    memset(visit, false, sizeof (visit));
    memset(p, -1, sizeof (p));
    memset(low, 0, sizeof(low));
    fill(&dist[0], &dist[maxn], -inf);
    visit[s] = true, low[s] = inf, dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
            if (flow < cap && dist[u] + cost > dist[v]) {
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
    return dist[t] != -inf;
}
void costflow() {
    ans = 0, anscost = 0;
    while (spfa()) {
        int x = p[t];
        ans += low[t];
        anscost += low[t] * dist[t];
        while (x != -1) {
            et[x].flow += low[t];
            et[x^1].flow -= low[t];
            et[x^1].cost = -et[x].cost;
            x = p[et[x].u];
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        init();
        vector<int> vec;
        for(int i = 1; i <= n; i++) {
            scanf("%d%d%d", &a[i], &b[i], &w[i]);
            vec.pb(a[i]);
            vec.pb(b[i]);
        }
        vec.pb(0);
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        for(int i = 1; i < vec.size(); i++) id[vec[i]] = i;
        int cnt = vec.size() - 1;
        for(int i = 1; i < cnt; i++) addedge(i, i + 1, 0, inf);
        s = 0, t = cnt + 1;
        addedge(s, 1, 0, k);
        addedge(cnt, t, 0, k); 
        for(int i = 1; i <= n; i++) addedge(id[a[i]], id[b[i]], w[i], 1);
        costflow();
        printf("%d\n", anscost);
    }
    return 0;
}
