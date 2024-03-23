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

const int N = 111;
const int M = 3333;
int n, m;
bool used[N][M];
int sum[N];
int dist[N];
int eh[N], tot;
struct Edge {
    int v, id, next;
} et[M * 2];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v, int id) {
    Edge e = {v, id, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

pii edge[M];
bool in[N];
int bfs(int s, int forbid, int flag) {
    queue<int> que;
    memset(dist, -1, sizeof(dist));
    dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = eh[u]; ~i; i = et[i].next) {
            if (et[i].id == forbid) continue;
            int v = et[i].v;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
    int t = 0;
    for (int i = 0; i < n; i++) {
        t += dist[i];
        if (dist[i] == -1) {
            t = -1;
            break;
        }
    }
    if (flag) return t;
    sum[s] = t;
    memset(used[s], 0, sizeof(used[s]));
    memset(in, 0, sizeof(in));
    for (int i = 0; i < m; i++) {
        int a = edge[i].fi, b = edge[i].se;
        if (dist[a] + 1 == dist[b] && !in[b]) used[s][i] = in[b] = true;
        if (dist[b] + 1 == dist[a] && !in[a]) used[s][i] = in[a] = true;
    }
    return t;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        init();
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--, b--;
            edge[i] = mp(a, b);
            addedge(a, b, i);
            addedge(b, a, i);
        }
        for (int i = 0; i < n; i++) bfs(i, -1, 0);
        for (int i = 0; i < m; i++) {
            int ans = 0;
            int a = edge[i].fi, b = edge[i].se;
            for (int j = 0; j < n; j++) {
                if (used[j][i]) {
                    int ret = bfs(j, i, 1);
                    if (ret == -1) {
                        ans = -1;
                        break;
                    }
                    ans += ret;
                } else {
                    if (sum[j] == -1) {
                        ans = -1;
                        break;
                    }
                    ans += sum[j];
                }
            }
            if (ans == -1) puts("INF");
            else printf("%d\n", ans);
        }
    }
    return 0;
}
