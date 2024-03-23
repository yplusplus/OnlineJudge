//强连通缩点后，找出度为0的强连通分量的个数，如果为1个，则该连通分量所有点满足条件，否则所有点都不满足条件。
//用vector 813MS 用手写邻接表 360MS vector太慢了
#include "iostream"
#include "cstdio"
#include "algorithm"
#include "vector"
#include "cstring"
using namespace std;
#define maxn 10005
#define maxm 50005
int n, m;
int dfn[maxn], low[maxn], belong[maxn], s[maxn], top, Dindex, cnt;
int eh[maxn], num[maxn], tot, out[maxn];
bool instack[maxn];
vector<int> vec[maxn];

void tarjan(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	instack[u] = true;
	s[++top] = u;
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
			num[cnt]++;
		}while(v != u);
	}
}

void solve() {
	top = cnt = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, 0, sizeof(instack));
	for(int i = 1; i <= n; i++) 
		if(!dfn[i]) tarjan(i);
}

int main() {
	int u, v;
	cin >> n >> m;
	memset(num, 0, sizeof(num));
	for(int i = 0; i < m; i++) {
		cin >> u >> v;
		vec[u].push_back(v);
	}
	solve();
	for(int u = 1; u <= n; u++) {
		int size = vec[u].size();
		for(int i = 0; i < size; i++) {
			v = vec[u][i];
			if(belong[u] != belong[v]) out[belong[u]]++;
		}
	}
	int index, nn = 0;
	for(int i = 1; i <= cnt; i++) {
		if(out[i] == 0) {
			nn++;
			index = i;
		}
	}
	if(nn == 1) cout << num[index] << endl;
	else cout << '0' << endl;
}