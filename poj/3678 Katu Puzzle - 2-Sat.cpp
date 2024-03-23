#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 2500
#define maxm 5000000
int n, m;
int eh[maxn], tot;
int belong[maxn], scc, dfn[maxn], low[maxn], Dindex;
int s[maxn], top;
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
		}while(v != u);
	}
}

void tarjan() {
	top = scc = Dindex = 0;
	memset(instack, false, sizeof(instack));
	memset(dfn, 0, sizeof(dfn));
	for(int i = 0; i < 2 * n; i++)
		if(!dfn[i]) dfs(i);
}

bool solvable() {
	for(int i = 0; i < 2 * n; i += 2)
		if(belong[i] == belong[i^1]) return false;
	return true;
}

void build(int u, int v, int c, char *s) {
	int a = 2 * u, b = 2 * v;
	if(strcmp(s, "AND") == 0) {
		if(c) addedge(a, a^1), addedge(b, b^1);
		else addedge(a^1, b), addedge(b^1, a);
	} else if(strcmp(s, "OR") == 0) {
		if(c) addedge(a, b^1), addedge(b, a^1);
		else addedge(a^1, a), addedge(b^1, b);
	} else {
		if(c) addedge(a, b^1), addedge(b, a^1), addedge(a^1, b), addedge(b^1, a);
		else addedge(a, b), addedge(a^1, b^1), addedge(b, a), addedge(b^1, a^1);
	}
}

int main() {
	char s[5];
	int u, v, c;
	while(~scanf("%d%d", &n, &m)) {
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d%s", &u, &v, &c, s);
			build(u, v, c, s);
		}
		tarjan();
		if(solvable()) printf("YES\n");
		else printf("NO\n");
		break;
	}
	return 0;
}