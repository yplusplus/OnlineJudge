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
#define maxm 2222222
#define maxn 2050
int eh[maxn], cur[maxn], tot;
int n, m, s, t, nn;
int dist[maxn];
int que[maxn];
char s1[1010], s2[1010];
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
    int head = 0, tail = 0;
    memset(dist, -1, sizeof(dist));
    dist[t] = 0;
    que[tail++] = t;
    while(head < tail && dist[s] == -1) {
        int u = que[head++];
        for(int i = eh[u]; i != -1; i = et[i].next) {
            if(et[i^1].cap > et[i^1].flow && dist[et[i].v] == -1) {
                dist[et[i].v] = dist[u] + 1;
                que[tail++] = et[i].v;
            }
        }
    }
    return dist[s] != -1;
}
int dfs(int u, int d) {
    if(u == t) return d;
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
        for(int i = 0; i < nn; i++) cur[i] = eh[i];
        flow += dfs(s, inf);
    }
    return flow;
}

int main() {
    scanf("%s%s", s1, s2);
    int n = strlen(s1), m = strlen(s2);
    s = n + m, t = n + m + 1;
    nn = n + m + 2;
    init();
    for(int i = 0; i < n; i++) {
        if(s1[i] == '0') addedge(s, i, inf);
        else if(s1[i] == '1') addedge(i, t, inf);
    }
    for(int i = 0; i < m; i++) {
        if(s2[i] == '0') addedge(s, i + n, inf);
        else if(s2[i] == '1') addedge(i + n, t, inf);
    }
    for(int i = 0; i + m <= n; i++) {
        for(int j = 0; j < m; j++) {
            addedge(i + j, n + j, 1);
            addedge(n + j, i + j, 1);
        }
    }
    printf("%d\n", Dinic());
    for(int i = 0; i < n; i++) {
        printf("%c", dist[i] == -1 ? '0' : '1');
    }
    printf("\n");
    for(int i = 0; i < m; i++) {
        printf("%c", dist[i+n] == -1 ? '0' : '1');
    }
    printf("\n");
    return 0;
}
