#include "iostream"
#include "cstdio"
#include "vector"
#include "cstring"
#include "algorithm"
using namespace std;
#define maxn 4005
vector<int> vec[maxn];
int n, tot;
int dfn[maxn], low[maxn], cnt, top, instack[maxn], s[maxn], Dindex, belong[maxn], ans[maxn];
void tarjan(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u;
	instack[u] = true;
	int size = vec[u].size();
	for(int i = 0; i < size; i++) {
		v = vec[u][i];
		if(!dfn[v]) {
			tarjan(v);
			if(low[v] < low[u]) low[u] = low[v];
		} else if(instack[v] && dfn[v] < low[u]) low[u] = dfn[v];
	}
	if(dfn[u] == low[u]) {
		cnt++;
		do {
			v = s[top--];
			instack[v] = false;
			belong[v] = cnt;
		} while(v != u);
	}
}

void solve() {
	cnt = top = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, 0, sizeof(instack));
	for(int i = 1; i <= 2 * n; i++) 
		if(!dfn[i]) tarjan(i);
}

int main() {
	int num, v;
	scanf("%d", &n);
	for(int i = 1; i <= 2 * n; i++) vec[i].clear();
	for(int u = 1; u <= n; u++) {
		scanf("%d", &num);
		for(int i = 1; i <= num; i++) {
			scanf("%d", &v);
			vec[u].push_back(n+v);
		}
	}
	for(int u = 1; u <= n; u++) {
		scanf("%d", &v);
		vec[n+v].push_back(u);
	}
	solve();
	for(int i = 1; i <= n; i++) {
		int size = vec[i].size();
		tot = 0;
		for(int j = 0; j < size; j++) {
			int v = vec[i][j];
			if(belong[i] == belong[v]) 
				ans[tot++] = v - n;
		}
		sort(ans, ans + tot);
		printf("%d", tot);
		for(int j = 0; j < tot; j++) printf(" %d", ans[j]);
		printf("\n");
	}
	return 0;
}