#include "iostream"
#include "cstring"
#include "cstdio"
#include "vector"
using namespace std;
#define maxn 5010
vector<int> vec[maxn], rvec[maxn], dag[maxn];
int belong[maxn], scc, top, s[maxn], color[maxn];
int n, m;
bool visit[maxn];
void init() {
	for(int i = 0; i < maxn; i++)
		vec[i].clear(), rvec[i].clear(), dag[i].clear();
}

int cal(int a, char ch) {
	int res = a * 2;
	if(ch == 'h') return res;
	else return res + 1;
}

void dfs1(int u) {
	visit[u] = true;
	int size = vec[u].size();
	for(int i = 0; i < size; i++) {
		int v = vec[u][i];
		if(!visit[v]) dfs1(v);
	}
	s[++top] = u;
}

void dfs2(int u) {
	visit[u] = true;
	int size = rvec[u].size();
	for(int i = 0; i < size; i++) {
		int v = rvec[u][i];
		if(!visit[v]) dfs2(v);
	}
	belong[u] = scc;
}

void kosaraju() {
	scc = top = 0;
	memset(visit, false, sizeof(visit));
	for(int i = 0; i < 2 * n; i++) 
		if(!visit[i]) dfs1(i);
	memset(visit, false, sizeof(visit));
	for(int i = 2 * n; i; i--) 
		if(!visit[s[i]]) scc++, dfs2(s[i]);
	for(int u = 0; u < 2 * n; u++) {
		int size = rvec[u].size();
		for(int i = 0; i < size; i++) {
			int v = rvec[u][i];
			if(belong[u] != belong[v]) dag[belong[u]].push_back(belong[v]);
		}
	}
}

bool solvable() {
	for(int i = 0; i < 2 * n; i += 2)
		if(belong[i] == belong[i+1]) return false;
	return true;
}

void dfs(int u) {
	color[u] = 2;
	int size = dag[u].size();
	for(int i = 0; i < size; i++) {
		int v = dag[u][i];
		if(!color[v]) dfs(v);
	}
}

void solve() {
	memset(color, 0, sizeof(color));
	for(int i = scc; i; i--) {
		if(!color[i]) {
			color[i] = 1;
			for(int j = 0; j < 2 * n; j++) {
				if(belong[j] == i) {
					int k = belong[j^1];
					if(!color[k]) dfs(k);
				}
			}
		}
	}
	for(int i = 2; i < 2 * n; i++)
		if(color[belong[i]] == color[belong[1]])
			printf("%d%c ", i / 2, i & 1 ? 'w' : 'h');
	printf("\n");
}

void debug() {
	for(int i = 0; i < 2 * n; i++) {
		int size = vec[i].size();
		for(int j = 0; j < size; j++) {
			cout << i << "->" << vec[i][j] << endl;
		}
	}
	cout << endl;
	for(int i = 1; i <= scc; i++) {
		int size = dag[i].size();
		for(int j = 0; j < size; j++) {
			cout << i << "->" << dag[i][j] << endl;
		}
	}
}

int main() {
	char ch1, ch2;
	int a, b;
	while(~scanf("%d%d", &n, &m)) {
		getchar();
		if(!n && !m) break;
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%c%d%c", &a, &ch1, &b, &ch2);
			getchar();
			int u = cal(a, ch1), v = cal(b, ch2);
			vec[u].push_back(v^1), vec[v].push_back(u^1);
			rvec[v^1].push_back(u), rvec[u^1].push_back(v);
		}
		vec[1].push_back(0), rvec[0].push_back(1);
		kosaraju();
		if(solvable()) solve();
		else printf("bad luck\n");
	}
	return 0;
}