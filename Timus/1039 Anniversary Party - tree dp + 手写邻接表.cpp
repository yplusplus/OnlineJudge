#include "iostream"
#include "cstring"
#include "algorithm"
using namespace std;
#define maxn 6100
#define maxm 6100
int dp[maxn][2], eh[maxn], tot, root;
bool visit[maxn];
struct Edge {
	int v, next;
}et[maxm];

int max(int a, int b) {
	return a > b ? a : b;
}

void init() { 
	tot = 0;
	memset(eh, -1, sizeof(eh));
	memset(visit, false, sizeof(visit));
}

void addedge(int u, int v) {
	Edge E = {v, eh[u]};
	et[tot] = E;
	eh[u] = tot++;
}

void dfs(int u) {
	for(int i = eh[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		dfs(v);
		dp[u][0] += max(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][0];
	}
}
int main () {
	int n, l, k, i;
	init();
	cin >> n;
	for(i = 1; i <= n; i++)
		cin >> dp[i][1], dp[i][0] = 0;
	while(1) {
		cin >> l >> k;
		visit[l] = true;
		if(l == 0 && k == 0) break;
		addedge(k, l);
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
