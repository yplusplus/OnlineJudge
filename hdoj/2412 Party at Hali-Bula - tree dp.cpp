#include "iostream"
#include "vector"
#include "map"
#include "string"
#include "cstring"
using namespace std;
#define maxn 205
vector<int> vec[maxn];
int tot;
int dp[maxn][2];
bool uni[maxn][2];

void init() {
	tot = 1;
	for(int i = 0; i < maxn; i++)
		vec[i].clear();
}

void dfs(int u) {
	dp[u][0] = 0, dp[u][1] = 1;
	uni[u][0] = uni[u][1] = true;
	int size = vec[u].size();
	for(int i = 0; i < size; i++) {
		int v = vec[u][i];
		dfs(v);
		dp[u][1] += dp[v][0];
		if(!uni[v][0]) uni[u][1] = false;
		if(dp[v][0] > dp[v][1]) {
			dp[u][0] += dp[v][0];
			if(!uni[v][0]) uni[u][0] = false;
		} else if(dp[v][0] < dp[v][1]) {
			dp[u][0] += dp[v][1];
			if(!uni[v][1]) uni[u][0] = false;
		} else {
			dp[u][0] += dp[v][1];
			uni[u][0] = false;
		}
	}
}
	

int main() {
	int n, u, v;
	char s[1005], t[1005];
	while(scanf("%d", &n), n) {
		scanf("%s", s);
		init();
		map<string, int> m;
		m[(string)s] = tot++;
		for(int i = 1; i < n; i++) {
			scanf("%s%s", s, t);
			if(!m[s]) m[s] = tot++;
			if(!m[t]) m[t] = tot++;
			vec[m[t]].push_back(m[s]);
		}
		vec[0].push_back(1);
		dfs(0);
		printf("%d ", dp[0][0]);
		if(uni[0][0]) printf("Yes\n");
		else printf("No\n");
	}
	return 0;

}