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

#define maxn 5050
#define maxm 5000000
int n, m;
int dfn[maxn], low[maxn], Dindex, belong[maxn], scc;
int s[maxn], top;
int eh[maxn], tot;
bool instack[maxn];
struct Edge {
	int v, next;
}et[maxm];
void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}
void addedge(int u, int v) {
	Edge e = {v, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}
void dfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u, instack[u] = true;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		v = et[i].v;
		if(!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
		else if(instack[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		scc++;
		do {
			v = s[top--];
			instack[v] = false;
			belong[v] = scc;
		} while(u != v);
	}
}
void tarjan() {
	top = scc = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, false, sizeof(instack));
	for(int i = 1; i <= 2 * n; i++)
		if(!dfn[i]) dfs(i);
}
bool solvable() {
	for(int i = 1; i <= n; i++)
		if(belong[i] == belong[i+n]) return false;
	return true;
}
int main() {
	int a, b, aa, bb;
	while(~scanf("%d%d", &n, &m)) {
		init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &a, &b);
            aa = abs(a), bb = abs(b);
            if(a > 0 && b > 0) addedge(aa + n, bb), addedge(bb + n, aa);
            else if(a > 0 && b < 0) addedge(aa + n, bb + n), addedge(bb, aa);
            else if(a < 0 && b > 0) addedge(aa, bb), addedge(bb + n, aa + n);
            else addedge(aa, bb + n), addedge(bb, aa + n);
        }
		tarjan();
        puts(solvable() ? "1" : "0");
	}
	return 0;
}

