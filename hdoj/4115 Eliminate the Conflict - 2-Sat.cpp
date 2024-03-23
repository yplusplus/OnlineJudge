#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
#define MAX 10500
#define maxn 20500
#define maxm 10000000
int n, m;
int Bob[MAX], Alice[MAX][2];
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
	int T, Case = 1;
	int a, b, c;
	scanf("%d", &T);
	while(T--) {
		init();
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &Bob[i]);
			if(Bob[i] == 1) Alice[i][0] = 1, Alice[i][1] = 2;
			else if(Bob[i] == 2) Alice[i][0] = 2, Alice[i][1] = 3;
			else Alice[i][0] = 3, Alice[i][1] = 1;
		}
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &a, &b, &c);
			if(c) {
				if(Alice[a][0] == Alice[b][0]) addedge(a, b + n), addedge(b, a + n);
				else if(Alice[a][0] == Alice[b][1]) addedge(a, b), addedge(b + n, a + n);
				if(Alice[a][1] == Alice[b][0]) addedge(a + n, b + n), addedge(b, a);
				else if(Alice[a][1] == Alice[b][1]) addedge(a + n, b), addedge(b + n, a);
			} else {
				if(Alice[a][0] != Alice[b][0]) addedge(a, b + n), addedge(b, a + n);
				if(Alice[a][0] != Alice[b][1]) addedge(a, b), addedge(b + n, a + n);
				if(Alice[a][1] != Alice[b][0]) addedge(a + n, b + n) , addedge(b, a);
				if(Alice[a][1] != Alice[b][1]) addedge(a + n, b), addedge(b + n, a);
			}
		}
		tarjan();
		printf("Case #%d: ", Case++);
		if(solvable()) printf("yes\n");
		else printf("no\n");

	}
	return 0;
}