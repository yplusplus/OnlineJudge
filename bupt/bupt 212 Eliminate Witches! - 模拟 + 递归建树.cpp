#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;
#define maxn 50500
char str[1005000];
char room[maxn][15];
int tot, ind, len;
vector<int> vec[maxn];
void dfs(int fa) {
	int now = tot++, p = 0;
	vec[fa].push_back(now);
	for(ind++; ind < len; ind++) {
		if(str[ind] == '(') dfs(now);
		else if(str[ind] == ')') return;
		else if(str[ind] == ',') {
			dfs(fa);
			return;
		}
		else room[now][p++] = str[ind], room[now][p] = '\0';
	}
}

void dfs2(int u) {
	int size = vec[u].size();
	for(int i = 0; i < size; i++) {
		int v = vec[u][i];
		printf("%d %d\n", u, v);
		dfs2(v);
		printf("%d %d\n", v, u);
	}
}

void solve() {
	tot = 1, ind = -1;
	scanf("%s", str);
	len = strlen(str);
	for(int i = 0; i < maxn; i++) vec[i].clear();
	dfs(0);
	printf("%d\n", tot - 1);
	for(int i = 1; i < tot; i++) printf("%s\n", room[i]);
	dfs2(1);
	printf("\n");
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) solve();
	return 0;
}