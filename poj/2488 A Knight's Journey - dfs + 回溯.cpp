#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define MAX 30
const int dx[]={-2, -2, -1, -1, 1, 1, 2, 2}; 
const int dy[]={-1, 1, -2, 2, -2, 2, -1, 1}; 
bool visit[MAX][MAX], flag;
int p, q, path[MAX][2];
int step;

bool check(int x, int y) {
	if(x >= 1 && x <= q && y >= 1 && y <= p) return true;
	return false;
}

void dfs(int x, int y, int cnt) {
	visit[x][y] = true;
	path[cnt][0] = x, path[cnt][1] = y;
	if(step == cnt) flag = false;
	for(int i = 0; i < 8 && flag; i++) {
		int xx = x + dx[i], yy = y + dy[i];
		if(check(xx, yy) && !visit[xx][yy]) {
			dfs(xx, yy, cnt + 1);
			visit[xx][yy] = false;
		}
	}
}

void init() {
	for(int i = 1; i < MAX; i++) memset(visit[i], false, sizeof(visit[i]));
	flag = 1;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int tt = 1; tt <= T; tt++) {
		init();
		scanf("%d%d", &p, &q);
		step = p * q;	
		for(int i = 1; i <= q && flag; i++) {
			for(int j = 1; j <= p && flag; j++) {
				dfs(i, j, 1);
			}
		}
		printf("Scenario #%d:\n", tt);
		if(flag) printf("impossible\n\n");
		else {
			for(int i = 1; i <= step; i++)
				printf("%c%d", path[i][0] + 'A' - 1, path[i][1]);
			printf("\n\n");
		}
	}
	return 0;
}