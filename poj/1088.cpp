#include "iostream"
using namespace std;
#define MAX 105
int maz[MAX][MAX], h[MAX][MAX];
int r, c;
int xxx[] = {1, 0, -1, 0};
int yyy[] = {0, 1, 0, -1};

int dfs(int x, int y) {
	if(h[x][y]) return h[x][y];
	int maxh = 0;	
	for(int i = 0; i < 4; i++) {
		int xx = x + xxx[i], yy = y + yyy[i];	
		if(xx <= r && xx >= 1 && yy >= 1 && yy <= c && maz[x][y] > maz[xx][yy]) {
			h[xx][yy] = dfs(xx, yy);
			if(maxh < h[xx][yy])
				maxh = h[xx][yy];
		}
	}
	return maxh + 1;
}

int main() {
	cin >> r >> c;
	int i, j;
	int ans = 0;
	for(i = 1; i <= r; i++) 
		for(j = 1; j <= c; j++)
			cin >> maz[i][j];
	for(i = 1; i <= r; i++) 
		for(j = 1; j <= c; j++) {
			h[i][j] = dfs(i, j);
			if(ans < h[i][j])
				ans = h[i][j];
		}
	cout << ans << endl;
	return 0;
}