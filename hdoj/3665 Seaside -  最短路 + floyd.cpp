#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define maxn 15
int n;
int maz[maxn][maxn];
const int inf = 1 << 30;

void floyd() {
	for(int k = 0; k < n; k++) 
		for(int i = 0; i < n; i++) 
			if(maz[i][k] != inf)
				for(int j = 0; j < n; j++) 
					maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
}

int main() {
	int a, b, c, d;
	while(~scanf("%d", &n)) {
		queue<int> que;
		for(int i = 0; i < maxn; i++)
			for(int j = 0; j < maxn; j++)
				maz[i][j] = inf;
		for(int i = 0; i < n; i++) {
			scanf("%d%d", &a, &b);
			if(b) que.push(i);
			for(int j = 0; j < a; j++) {
				scanf("%d%d", &c, &d);
				maz[i][c] = d;
			}
		}
		floyd();
		int ans = inf;
		while(!que.empty()) {
			a = que.front();
			que.pop();
			ans = min(ans, maz[0][a]);
		}
		printf("%d\n", ans);
	}
	return 0;
}