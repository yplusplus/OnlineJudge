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
const int M = 55555;
const int N = 555;
int eh[N], tot;
int n, m;
struct Edge {
    int u, v, next;
}et[M];

void addedge(int u, int v) {
    Edge e = {u, v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}
int visit[N];
int ans;
int fa[N];
void bfs(int s) {
    memset(visit, -1, sizeof(visit));
    memset(fa, -1, sizeof(fa));
    queue<int> que;
    que.push(s);
    visit[s] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if ((visit[u] - 1) * 2 >= ans) return;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            if (v == fa[u]) continue;
            if (visit[v] == -1) {
                visit[v] = visit[u] + 1;
                fa[v] = u;
                que.push(v);
            } else {
                ans = min(ans, visit[v] + visit[u] + 1);
            }
        }
    }
}
int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        init();
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        ans = inf;
        for (int i = 0; i < n; i++) {
            bfs(i);
        }
        printf("Case %d: ", Case++);
        if (ans == inf) puts("impossible");
        else printf("%d\n", ans);
    }
    return 0;
}
