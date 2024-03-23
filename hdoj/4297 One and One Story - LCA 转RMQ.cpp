#pragma comment(linker, "/STACK:16777216") 
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

#define maxn 500050
int n, q;
int fa[maxn], eh[maxn], tot;
int deleteEdge[maxn];
int dis[maxn];
int F[maxn*2], B[maxn*2], pos[maxn];
int rmq[maxn*2][20], rn;
struct Edge {
    int u, v, next;
}et[maxn<<1];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
    for(int i = 1; i < maxn; i++) fa[i] = i;
}

void addedge(int u, int v) {
    Edge e = {u, v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

int find(int x) {
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(fa[a]), b = find(fa[b]);
    if(a == b) return false;
    if(a != b) fa[a] = b;
    return true;
}

void dfs(int u, int pre, int deep) {
    F[++rn] = u, B[rn] = deep, pos[u] = rn;
    for(int son = eh[u]; son != -1; son = et[son].next) {
        int v = et[son].v;
        if(v == pre) continue;
        dis[v] = dis[u] + 1;
        dfs(v, u, deep + 1);
        F[++rn] = u, B[rn] = deep;
    }
}
void Init_RMQ() {
    for(int i = 1; i <= rn; i++) rmq[i][0] = i;
    for(int j = 1; (1<<j) <= rn; j++) {
        for(int i = 1; i + (1<<j) - 1 <= rn; i++) {
            int a = rmq[i][j-1], b = rmq[i+(1<<(j-1))][j-1];
            if(B[a] < B[b]) rmq[i][j] = a;
            else rmq[i][j] = b;
        }
    }
}
int RMQ(int a, int b) {
    int k = int(log(1.0 + b - a) / log(2.0));
    int u = rmq[a][k], v = rmq[b-(1<<k)+1][k];
    if(B[u] < B[v]) return F[u];
    else return F[v];
}
int LCA(int a, int b) {
    a = pos[a], b = pos[b];
    if(a > b) return RMQ(b, a);
    else return RMQ(a, b);
}

void update(int &xans, int &yans, int xtmp, int ytmp) {
    int maxx = max(xans, yans), minn = min(xans, yans);
    int maxxtmp = max(xtmp, ytmp), minntmp = min(xtmp, ytmp);
    if(maxxtmp < maxx || (maxxtmp == maxx && minntmp < minn) || (maxxtmp == maxx && minntmp == minn && xans < yans)) {
        xans = xtmp, yans = ytmp;
    }
}

int main(){
    while(~scanf("%d%d", &n, &q)) {
        init();
        for(int i = 1; i <= n; i++) {
            int father;
            scanf("%d", &father);
            if(!Union(i, father)) {
                deleteEdge[i] = father;
            } else addedge(father, i), addedge(i ,father);
        }
        for(int i = 1; i <= n; i++) {
            if(i == fa[i]) {
                addedge(0, i);
                addedge(i, 0);
            }
        }
        rn = 0;
        dis[0] = 0;
        dfs(0, -1, 0);
        Init_RMQ();
        while(q--) {
            int a, b;
            scanf("%d%d", &a, &b);
            int ablca = LCA(a, b);
            if(ablca == 0) printf("-1 -1\n");
            else {
                int subroot = find(fa[a]);
                int xans = dis[a] - dis[ablca], yans = dis[b] - dis[ablca];
                int v = deleteEdge[subroot];
                int avlca = LCA(a, v), bvlca = LCA(b, v);
                int xtmp = dis[a] - dis[avlca], ytmp = dis[b] - dis[bvlca];
                if(dis[avlca] < dis[bvlca]) {
                    update(xans, yans, xtmp + dis[avlca] - dis[subroot] + 1 + dis[v] - dis[bvlca], ytmp);
                    update(xans, yans, xtmp, ytmp + dis[bvlca] - dis[avlca]);
                } else {
                    update(xans, yans, xtmp, ytmp + dis[bvlca] - dis[subroot] + 1 + dis[v] - dis[avlca]);
                    update(xans, yans, xtmp + dis[avlca] - dis[bvlca], ytmp);
                }
                printf("%d %d\n", xans, yans);
            }
        }
    }
    return 0;
}
