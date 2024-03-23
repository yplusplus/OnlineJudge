#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
using namespace std;
#define maxn 5005
#define maxm 100005

int tot, dfn[maxn], low[maxn], Dindex, instack[maxn], belong[maxn], cnt;
int s[2*maxn], top;
int eh[maxn], n, m, out[maxn], ans[maxn];

struct Edge {
	int v, next;
}et[maxm];

void addedge(int u, int v) {
	Edge E = {v, eh[u]};
	et[tot] = E;
	eh[u] = tot++;
}

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void tarjan(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	instack[u] = true;
	s[++top] = u;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		v = et[i].v;
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
		}while(v != u);
	}
}

void solve() {
	tot = cnt = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, 0, sizeof(instack));
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan(i);
}

int main() {
	while(cin >> n) {
		if(!n) break;
		init();
		cin >> m;
		for(int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			addedge(u, v);
		}
		solve();
		memset(out, 0, sizeof(out));
		for(int i = 1; i <= n; i++) {
			for(int j = eh[i]; j != -1; j = et[j].next) {
				int v = et[j].v;
				if(belong[i] != belong[v]) out[belong[i]]++;
			}
		}
		int index = 0;
		for(int i = 1; i <= n; i++) {
			if(out[belong[i]] == 0)
				ans[index++] = i;
		}
		sort(ans, ans + index);
		for(int i = 0; i < index; i++)
			printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}