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
#define maxm 200000
bool maz[maxn][maxn];
bool isDeleted[maxn];
int dist[maxn];
int eh[maxn], cur[maxn], tot;
int n, s, t, ss, tt;
struct Edge {
    int u, v, cap, flow, next;
}et[maxm];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
    Edge e = {u, v, cap, flow, eh[u]};
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
    dist[tt] = 0;
    que[tail++] = tt;
    while(head < tail && dist[ss] == -1) {
        int u = que[head++];
        for(int i = eh[u]; i != -1; i = et[i].next) {
            if(et[i^1].cap > et[i^1].flow && dist[et[i].v] == -1) {
                dist[et[i].v] = dist[u] + 1;
                que[tail++] = et[i].v;
            }
        }
    }
    return dist[ss] != -1;
}

int dfs(int u, int d) {
    if(u == tt) return d;
    int l = d;
    for(int &i = cur[u]; i != -1; i = et[i].next) {
        if(et[i].cap > et[i].flow && dist[u] == dist[et[i].v] + 1) {
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
        for(int i = 1; i <= (n << 1); i++) cur[i] = eh[i];
        flow += dfs(ss, inf);
    }
    return flow;
}

void build() {
    init();
    for(int i = 1; i <= n; i++) {
        if(isDeleted[i]) continue;
        addedge(i, i + n, 1);
        for(int j = 1; j <= n; j++) {
            if(isDeleted[j] || !maz[i][j] || i == j) continue;
            addedge(i + n, j, inf);
        }
    }
}

void solve() {
    int curflow;
    memset(isDeleted, false, sizeof(isDeleted));
    ss = s + n, tt = t;
    build();
    curflow = Dinic();
    vector<int> vec;
    vec.clear();
    for(int i = 1; i <= n && curflow != 0; i++) {
        if(i == s || i == t) continue;
        isDeleted[i] = true;
        build();
        int tmpflow = Dinic();
        if(tmpflow < curflow) {
            curflow = tmpflow;
            vec.pb(i);
        } else isDeleted[i] = false;
    }
    printf("%d\n", vec.size());
    for(int i = 0; i < vec.size(); i++) {
        if(i == vec.size() - 1) printf("%d\n", vec[i]);
        else printf("%d ", vec[i]);
    }
}
int main() {
    while(~scanf("%d%d%d", &n, &s, &t)) {
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                scanf("%d", &maz[i][j]);
        if(maz[s][t]) {
            puts("NO ANSWER!");
            continue;
        }
        solve();
    }
    return 0;
}
