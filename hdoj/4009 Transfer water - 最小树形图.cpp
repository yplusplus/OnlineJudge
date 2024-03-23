#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;
#define maxn 1005
#define maxm 1005000
int n, m;
#define type int
const type inf = 1 << 30;
int pre[maxn],id[maxn],visit[maxn], tot;
type in[maxn];
int root;
struct house {
	int x, y, z;
}h[maxn];
struct Edge {
    int u,v;
    type cost;
}et[maxm];

void init() {
	tot = 0;
}

void addedge(int u, int v, type cost) {
	Edge e = {u, v, cost};
	et[tot++] = e;
}

type getdist(int a, int b) {
	return abs(h[a].x - h[b].x) +abs(h[a].y - h[b].y) +abs(h[a].z - h[b].z);
}

type dirmst(int root,int nv,int ne) {//µãÊý+1,±ßÊý+1
    type ret = 0;
    while(1)
    {
        //find the smallest in-arc
        fill(&in[0], &in[maxn], inf);
        for(int i = 0; i < ne;i++) {
            int u = et[i].u, v = et[i].v;
            if(et[i].cost < in[v] && u != v)
                pre[v] = u, in[v] = et[i].cost;
        }
		//there are some nodes other than root with no in-arc connected to it
        for(int i = 0;i < nv;i++)
			if(in[i] == inf && i != root) return -1; 
        //find the dir circle
        int cntnode = 0;
		memset(id, -1, sizeof(id));
		memset(visit, -1, sizeof(visit));
        in[root] = 0;
        for(int i = 0;i < nv;i++) {
            ret += in[i];
            int v = i;
            while(visit[v] != i && id[v] == -1 && v != root)
                visit[v] = i, v = pre[v];
			if(v != root && id[v] == -1) {
                for(int u = pre[v]; u != v; u = pre[u])
                    id[u] = cntnode;
                id[v] = cntnode++;
            }
        }
        if(cntnode == 0) break;//no circle
        for(int i = 0;i < nv;i++)
            if(id[i] == -1) id[i] = cntnode++;
        //compress the nodes
        for(int i = 0;i < ne;i++) {
            int v = et[i].v;
            et[i].u = id[et[i].u];
            et[i].v = id[et[i].v];
            if(et[i].u != et[i].v)
                et[i].cost -= in[v];
        }
        nv = cntnode;
        root = id[root];
    }
    return ret;
}
int a, b, c, k, v;
int main() {
	while(~scanf("%d%d%d%d", &n, &a, &b, &c)) {
		if(!n && !a && !b && !c) break;
		init();
		root = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d%d%d", &h[i].x, &h[i].y, &h[i].z);
			addedge(root, i, h[i].z * a);
		}
		for(int i = 1; i <= n; i++) {
			scanf("%d", &k);
			for(int j = 0; j < k; j++) {
				scanf("%d", &v);
				if(v == i) continue;
				type cost = getdist(v, i) * b;
				if(h[i].z < h[v].z) cost += c;
				addedge(i, v, cost);
			}
		}
		type ans = dirmst(root, n + 1, tot);
		printf("%d\n", ans);
	}
	return 0;
}