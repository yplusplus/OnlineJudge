#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
#define MAXN 250
queue<int> que;
//g[i][j]存放关系图：i,j是否有边,match[i]存放i所匹配的点
bool g[MAXN][MAXN], visit[MAXN], inblossom[MAXN];
int match[MAXN], pre[MAXN], base[MAXN];
 
//找公共祖先
int findancestor(int u, int v) {
    bool inpath[MAXN];
    memset(inpath, false, sizeof(inpath));
    while(1) {
        u = base[u];
        inpath[u] = true;
        if(match[u] == -1) break;
        u = pre[match[u]];
    }
    while(1) {
        v = base[v];
        if(inpath[v]) return v;
        v = pre[match[v]];
    }
}
 
//压缩花
void reset(int u,int anc) {
    while(u != anc) {
        int v=match[u];
        inblossom[base[u]] = inblossom[base[v]] = true;
        v = pre[v];
        if(base[v] != anc) pre[v] = match[u];
        u = v;
    }
}
 
void contract(int u,int v,int n) {
    int anc = findancestor(u,v);
    memset(inblossom, 0, sizeof(inblossom));
    reset(u, anc), reset(v, anc);
    if(base[u] != anc) pre[u] = v;
    if(base[v] != anc) pre[v] = u;
    for(int i = 1; i <= n; i++)
        if(inblossom[base[i]]) {
            base[i] = anc;
            if(!visit[i]) {
                que.push(i);
                visit[i] = 1;
            }
        }
}
 
bool bfs(int S,int n) {
    for(int i = 0; i <= n; i++) pre[i] = -1, visit[i] = 0, base[i] = i;
    while(!que.empty()) que.pop();
    que.push(S);
    visit[S]=1;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        for(int v = 1; v <= n; v++) {
            if(g[u][v] && base[v] != base[u] && match[u] != v) {
                if(v == S || (match[v] != -1 && pre[match[v]] != -1)) contract(u,v,n);
                else if(pre[v] == -1) {
                    pre[v] = u;
                    if(match[v] != -1) que.push(match[v]), visit[match[v]] = 1;
                    else {
                        u = v;
                        while(u != -1) {
                            v = pre[u];
                            int w = match[v];
                            match[u] = v, match[v] = u;
                            u = w;
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
 
int Match(int n) {//n 是点数
    memset(match, -1, sizeof(match));
    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(match[i] == -1 && bfs(i, n)) ans++;
    return ans;
}

int main() {
    int u, v, n;
    scanf("%d", &n);
    memset(g, 0, sizeof(g));
    while(~scanf("%d%d", &u, &v)) g[u][v] = g[v][u] = 1;
    int ans = Match(n);
    cout << ans * 2 << endl;
    for(int i = 1; i <= n; i++)
        if(match[i] != -1 && i < match[i]) 
            cout << i << " " << match[i] << endl;
}
