#include "iostream"
#include "cstdio"
#include "vector"
#include "cstring"
using namespace std;
#define maxn 2005
vector<int> vec[maxn];
int d[maxn];
bool visit[maxn];
int n, m, flag;

void dfs(int u) {
	visit[u] = true;
	if(flag) return;
	int size = vec[u].size();
	for(int i = 0; i < size; i++) {
		if(flag) return;
		int v = vec[u][i];
		if(!visit[v]) { 
			d[v] = d[u] + 1;
			dfs(v);
		} else if((d[u] - d[v]) % 2 == 0) flag = 1;
	}
}

void init() {
	for(int i = 0; i <= n; i++) vec[i].clear();
	memset(visit, 0, sizeof(visit));
	flag = 0;
}

int main() {
	int t = 1, nt, u, v, i;
	scanf("%d", &nt);
	while(t <= nt) {
		cin >> n >> m;
		init();
		for(i = 0; i < m; i++) {
			cin >> u >> v;
			vec[u].push_back(v);
			vec[v].push_back(u);
		}
		for(i = 1; i <= n; i++) {
			if(!visit[i]) {
				if(flag) break;
				d[i] = 1;
				dfs(i);
			}
		}
		printf("Scenario #%d:\n", t++);
		if(flag) printf("Suspicious bugs found!\n\n");
		else printf("No suspicious bugs found!\n\n");
	}
	return 0;
}