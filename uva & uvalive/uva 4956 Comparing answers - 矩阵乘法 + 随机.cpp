#include "iostream"
#include "cstdio"
#include "cstring"
#include "ctime"
#include "cstdlib"
using namespace std;
#define maxn 1050
int val[maxn][maxn], tmp[maxn][maxn], ans[maxn][maxn];
int n;
bool visit[maxn];
bool solve() {
	memset(tmp, 0, sizeof(tmp));
	memset(visit, false, sizeof(visit));
	if(n <= 100) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				for(int k = 0; k < n; k++) {
					tmp[i][j] += val[i][k] * val[k][j];
				}
				if(tmp[i][j] != ans[i][j]) return false;
			}
		}
		return true;
	}
	int cnt = 0;
	while(cnt < 10) {
		int k = rand() % n;
		if(visit[k]) continue;
		else visit[k] = true, cnt++;
		for(int j = 0; j < n; j++) {
			for(int i = 0; i < n; i++) {
				tmp[k][j] +=  val[k][i] * val[i][j];
			}
			if(tmp[k][j] != ans[k][j]) return false;
		}
	}
	return true;
}

int main() {
	srand(time(NULL));
	while(~scanf("%d", &n)) {
		if(!n) break;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				scanf("%d", &val[i][j]);
			}
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				scanf("%d", &ans[i][j]);
			}
		}
		if(solve()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}