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
const int N = 333;
const int M = 99999;

struct Costflow {
    int s, t;
    int ans, anscost;
    int dist[N], pre[N], low[N];
    int eh[N], tot;
    bool visit[N];
    struct Edge {
        int u, v, cost, cap, flow, next;
    } et[M];
    void init() {
        tot = 0;
        memset(eh, -1, sizeof(eh));
    }
    void add(int u, int v, int cost, int cap, int flow) {
        Edge e = {u, v, cost, cap, flow, eh[u]};
        et[tot] = e;
        eh[u] = tot++;
    }
    void addedge(int u, int v, int cost, int cap) {
        add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
    }
    bool findPath() {
        queue<int> que;
        memset(visit, false, sizeof(visit));
        memset(pre, -1, sizeof(pre));
        memset(low, 0, sizeof(low));
        for (int i = 0; i < N; i++) dist[i] = inf;
        dist[s] = 0, low[s] = inf;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            visit[u] = false;
            for (int i = eh[u]; ~i; i = et[i].next) {
                int v = et[i].v;
                if (et[i].cap > et[i].flow && dist[v] > dist[u] + et[i].cost) {
                    dist[v] = dist[u] + et[i].cost;
                    pre[v] = i;
                    low[v] = min(low[u], et[i].cap - et[i].flow);
                    if (!visit[v]) {
                        que.push(v);
                        visit[v] = true;
                    }
                }
            }
        }
        return dist[t] < inf;
    }
    void solve() {
        ans = anscost = 0;
        while (findPath()) {
            ans += low[t];
            anscost += low[t] * dist[t];
            int x = pre[t];
            while (x != -1) {
                et[x].flow += low[t];
                et[x ^ 1].flow -= low[t];
                x = pre[et[x].u];
            }
        }
    }
} costflow;
char str[N];
int r, c;
int main() {
    while (~scanf("%d%d", &r, &c)) {
        if (!r && !c) break;
        vector<pii> man, house;
        for (int i = 0; i < r; i++) {
            scanf("%s", str);
            for (int j = 0; j < c; j++) {
                if (str[j] == 'm') {
                    man.pb(mp(i, j));
                } else if (str[j] == 'H') {
                    house.pb(mp(i, j));
                }
            }
        }
        costflow.init();
        costflow.s = man.size() + house.size();
        costflow.t = costflow.s + 1;
        for (int i = 0; i < man.size(); i++) costflow.addedge(costflow.s, i, 0, 1);
        for (int j = 0; j < house.size(); j++) costflow.addedge(man.size() + j, costflow.t, 0, 1);
        for (int i = 0; i < man.size(); i++) {
            for (int j = 0; j < house.size(); j++) {
                costflow.addedge(i, man.size() + j, abs(man[i].fi - house[j].fi) + abs(man[i].se - house[j].se), 1);
            }
        }
        costflow.solve();
        printf("%d\n", costflow.anscost);
    }
    return 0;
}
