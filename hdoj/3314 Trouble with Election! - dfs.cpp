#include "iostream"
#include "cstdio"
#include "vector"
#include "queue"
#include "cstring"
using namespace std;
#define maxn 100100
int n, vote[maxn], now;
vector<int> vec[maxn];
queue<int> que;
void dfs(int u) {
	vote[now]++;
	int size = vec[u].size();
	for(int i = 0; i < size; i++)
		dfs(vec[u][i]);
}

int main() {
	int u;
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; i++) vec[i].clear();
		for(int i = 0; i < n; i++) {
			scanf("%d", &u);
			if(u == i) que.push(i); 
			else vec[u].push_back(i);
		}
		memset(vote, 0, sizeof(vote));
		while(!que.empty()) {
			now = que.front();
			que.pop();
			dfs(now);
		}
		int maxx = -1, k = -1, cnt = 0;
		for(int i = 0; i < n; i++) {
			if(vote[i] > maxx) maxx = vote[i], cnt = 1, k = i;
			else if(vote[i] == maxx) cnt++;
		}
		if(cnt == 1) printf("%d\n", k);
		else printf("Trouble\n");
	}
	return 0;
}