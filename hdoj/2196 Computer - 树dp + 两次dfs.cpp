#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;
#define pb push_back
#define maxn 10050
int n;
int down[maxn], up[maxn];
int rec[maxn][2], edge[maxn];
struct Edge {
    int v, w;
    Edge(){}
    Edge(int _v, int _w) {
        v = _v, w = _w;
    }
};
vector<Edge> g[maxn];

void dfs1(int u, int fa) {
    down[u] = 0;
    rec[u][0] = rec[u][1] = -1;
    int size = g[u].size();
    for(int i = 0; i < size; i++) {
        int v = g[u][i].v, w = g[u][i].w;
        if(v == fa) continue;
        dfs1(v, u);
        edge[v] = w;
        if(down[v] + w >= down[u]) {
            down[u] = down[v] + w;
            rec[u][1] = rec[u][0];
            rec[u][0] = v;
        } else if(rec[u][1] == -1 || down[v] + w > down[rec[u][1]] + edge[rec[u][1]]) rec[u][1] = v;
    }
}

void dfs2(int u, int fa) {
    up[u] = 0;
    if(fa != -1) {
        if(u == rec[fa][0]) {
            up[u] = up[fa] + edge[u];
            if(rec[fa][1] != -1) up[u] = max(up[u], down[rec[fa][1]] + edge[rec[fa][1]] + edge[u]);
        } else up[u] = max(up[fa], down[fa]) + edge[u];
    }
    int size = g[u].size();
    for(int i = 0; i < size; i++) {
        int v = g[u][i].v;
        if(v == fa) continue;
        dfs2(v, u);
    } 
}

int main() {
    int v, w;
    while(~scanf("%d", &n)) {
        for(int i = 0; i < maxn; i++) g[i].clear();
        for(int i = 2; i <= n; i++) {
            scanf("%d%d", &v, &w);
            g[i].pb(Edge(v, w));
            g[v].pb(Edge(i, w));
        }
        dfs1(1, -1);
        dfs2(1, -1);
        for(int i = 1; i <= n; i++) printf("%d\n", max(up[i], down[i]));
    }
    return 0;
}
