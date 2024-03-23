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

const int N = 3333;
const int M = N * N;
int eh[N], cur[N], tot;
int dist[N];
int n, m;
struct Edge {
    int u, v, cap, flow, next;
} et[M];

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

bool bfs(int s, int t) {
    queue<int> que;
    memset(dist, -1, sizeof(dist));
    que.push(s);
    dist[s] = 0;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (int i = eh[u]; ~i; i = et[i].next) {
            int v = et[i].v;
            if (dist[v] == -1 && et[i].cap > et[i].flow) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
    return dist[t] != -1;
}

int dfs(int u, int t, int d) {
    if (u == t) return d;
    int l = d;
    for (int &i = cur[u]; ~i; i = et[i].next) {
        int v = et[i].v;
        if (et[i].cap > et[i].flow && dist[v] == dist[u] + 1) {
            int tmp = dfs(v, t, min(et[i].cap - et[i].flow, l));
            et[i].flow += tmp;
            et[i ^ 1].flow -= tmp;
            l -= tmp;
            if (l == 0) break;
        }
    }
    return d - l;
}

int Dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        memcpy(cur, eh, sizeof(eh));
        flow += dfs(s, t, inf);
    }
    return flow;
}

int get_id(int x, int y) {
    return x * m + y;
}

char maz[50][50];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b, c;
        scanf("%d%d%d%d%d", &m, &n, &a, &b, &c);
        for (int i = 0; i < n; i++) scanf("%s", maz[i]);
        int s = n * m;
        int t = s + 1;
        init();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (check(nx, ny)) {
                        addedge(get_id(i, j), get_id(nx, ny), c);
                    }
                }
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    if (maz[i][j] == '.') addedge(s, get_id(i, j), b);//ans += b;
                    addedge(get_id(i, j), t, inf);
                } else {
                    if (maz[i][j] == '.') addedge(s, get_id(i, j), b);
                    else addedge(get_id(i, j), t, a);
                }
            }
        }
        cout << Dinic(s, t) << endl;
    }
    return 0;
}
