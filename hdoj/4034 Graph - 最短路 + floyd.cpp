#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 105
int maz[maxn][maxn], maz1[maxn][maxn];
bool visit[maxn][maxn];
int n;

int solve() {
	int cnt = 0;
	memset(visit, false, sizeof(visit));
	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			if(i != k)
				for(int j = 0; j < n; j++)
					if(j != k) {
						if(maz[i][j] == maz[i][k] + maz[k][j] && !visit[i][j]) cnt++, visit[i][j] = true;
						if(maz[i][j] > maz[i][k] + maz[k][j]) return -1;
					}
	return n * (n - 1) - cnt;
}

int main() {
	int T, tt = 1;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				scanf("%d", &maz[i][j]);
		int ans = solve();
		printf("Case %d: ", tt++);
		if(ans == -1) printf("impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}