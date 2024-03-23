#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;
#define maxn 1050
int n, m;
vector<int> vec[maxn];
int s[maxn], top;
int belong[maxn], scc, dfn[maxn], low[maxn], Dindex;
bool instack[maxn];
struct Line {
	int a, b;
}line[maxn];

void dfs(int u) {
	int v, size = vec[u].size();
	dfn[u] = low[u] = ++Dindex;
	instack[u] = true;
	s[++top] = u;
	for(int i = 0; i < size; i++) {
		v = vec[u][i];
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
	memset(dfn, 0, sizeof(dfn));
	memset(instack, 0, sizeof(instack));
	for (int u = 0; u < 2 * m; u++)
		if(!dfn[u]) dfs(u);
}

bool solvable() {
	for(int i = 0; i < 2 * m; i += 2) 
		if(belong[i] == belong[i^1]) return false;
	return true;
}

bool conflict(Line a, Line b) {
	if(a.a > b.b || a.b < b.a || (a.a < b.a && a.b > b.b) || (a.a > b.a && a.b < b.b)) return false;
	return true;
}

void build() {
	for(int i = 0; i < m; i++) {
		for(int j = i + 1; j < m; j++) {
			int u = 2 * i, v = 2 * j;
			if(conflict(line[i], line[j])) {
				vec[u].push_back(v^1), vec[u^1].push_back(v);
				vec[v].push_back(u^1), vec[v^1].push_back(u);
			}
		}
	}
}

int main() {
	for(int i = 0; i < maxn; i++) vec[i].clear();
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &line[i].a, &line[i].b);
		if(line[i].a > line[i].b) swap(line[i].a, line[i].b);
	}
	build();
	tarjan();
	if(solvable()) printf("panda is telling the truth...\n");
	else printf("the evil panda is lying again\n");
	return 0;
}