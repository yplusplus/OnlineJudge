#include "iostream"
#include "cstring"
#include "cstdio"
#include "vector"
using namespace std;
#define maxn 450
vector<int> vec[maxn];
int n, m;
int a[10500], b[10500], c[10500];
int dfn[maxn], low[maxn], s[maxn], top, scc, Dindex, belong[maxn];
bool instack[maxn];

void init() {
	for(int i = 0; i < maxn; i++) vec[i].clear();
}

void dfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u, instack[u] = true;
	int size = vec[u].size();
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
	scc = top = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, false, sizeof(instack));
	for(int i = 0; i < 2 * n; i++)
		if(!dfn[i]) dfs(i);
}

bool solvable() {
	for(int i = 0; i < 2 * n; i += 2)
		if(belong[i] == belong[i^1]) return false;
	return true;
}

void build(int mid) {
	init();
	for(int i = 0; i <= mid; i++) {
		int u = 2 * a[i], v = 2 * b[i];
		if(c[i] == 0) {
			vec[u].push_back(v^1), vec[v].push_back(u^1);
		} else if(c[i] == 1) {
			vec[u].push_back(v), vec[v].push_back(u);
			vec[u^1].push_back(v^1), vec[v^1].push_back(u^1);
		} else {
			vec[u^1].push_back(v), vec[v^1].push_back(u);
		}
	}
}

int solve() {
	int l = 0, r = m - 1, res = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		build(mid);
		tarjan();
		if(solvable()) res = mid + 1, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < maxn; i++) vec[i].clear();
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
		}
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}