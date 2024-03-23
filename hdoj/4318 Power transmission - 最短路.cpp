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
#define eps 1e-6
const double dinf = 1e30;
#define maxn 50050
#define maxm 3000000
int s, t, k;
double dist[maxn];
bool visit[maxn];
int n;
int eh[maxn], tot;
struct Edge {
    int v;
    double w;
    int next;
    Edge(){}
    Edge(int _v, double _w, int _next) {
        v = _v, w = _w, next = _next;
    }
}et[maxm];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v, double w) {
    Edge e;
    e.v = v, e.w = w, e.next = eh[u];
    et[tot] = e;
    eh[u] = tot++;
}
void spfa(int s) {
    for(int i = 1; i <= n; i++) dist[i] = -dinf;
    queue<int> que;
    que.push(s);
    visit[s] = 1;
    dist[s] = 1.0;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = 0;
        for(int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            double w = et[i].w;
            if(dist[v] + eps < dist[u] * w) {
                dist[v] = dist[u] * w;
                if(!visit[v]) {
                    que.push(v);
                    visit[v] = 1;
                }
            }
        } 
    }
}

int main() {
    int a, b, c, m;
    while(~scanf("%d", &n)) {
        init();
        for(int u = 1; u <= n; u++) {
            scanf("%d", &m);
            for(int i = 0; i < m; i++) {
                scanf("%d%d", &a, &b);
                addedge(u, a, 1.0 * (100.0 - b) / 100.0);
            }
        }
        scanf("%d%d%d", &s, &t, &k);
        spfa(s);
        if(dist[t] + eps < -dinf) puts("IMPOSSIBLE!");
        else printf("%.2lf\n", 1.0 * k * (1 - dist[t]));
    }
    return 0;
}
