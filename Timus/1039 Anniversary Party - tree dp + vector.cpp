#include "iostream"
#include "cstring"
#include "vector"
using namespace std;
#define maxn 6100
#define maxm 6100
vector<int> vec[maxn];
int dp[maxn][2], root;
bool visit[maxn];

int max(int a, int b) {
	return a > b ? a : b;
}

void dfs(int u) {
	int size = vec[u].size();
	for(int i = 0; i < size; i++) {
		int v = vec[u][i];
		dfs(v);
		dp[u][0] += max(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][0];
	}
}

int main () {
	int n, l, k, i;
	cin >> n;
	for(i = 1; i <= n; i++) {
		cin >> dp[i][1];
		dp[i][0] = 0;
		visit[i] = false;
		vec[i].clear();
	}
	while(1) {
		cin >> l >> k;
		visit[l] = true;
		if(l == 0 && k == 0) break;
		vec[k].push_back(l);
	}
	for(i = 1; i <= n; i++)
		if(!visit[i]) {
			root = i;
			break;
		}
	dfs(root);
	int ans = max(dp[root][0], dp[root][1]);
	printf("%d\n", ans);
	return 0;
}
