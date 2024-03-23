#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
const int MAX = 64;
const int r = 5, c = 6;
int map[10][10], ans[10][10], tmap[10][10];
const int dx[] = {0, 0, 0, -1, 1};
const int dy[] = {0, 1, -1, 0, 0};

bool check(int x, int y) {
	if(x >= 0 && x < r && y >= 0 && y < c) return true;
	return false;
}

void press(int x, int y) {
	for(int k = 0; k < 5; k++) {
		int xx = x + dx[k], yy = y + dy[k];
		if(check(xx, yy)) tmap[xx][yy] ^= 1;
	}
}

bool isOK() {
	for(int i = 1; i < r; i++) {
		for(int j = 0; j < c; j++) {
			if(tmap[i-1][j]) {
				ans[i][j] = 1;
				press(i, j);
			}
		}
	}
	for(int j = 0; j < c; j++) if(tmap[r-1][j]) return false;
	return true;
}

void solve() {
	for(int mask = 0; mask < MAX; mask++) {
		memset(ans, 0, sizeof(ans));
		memcpy(tmap, map, sizeof(map));
		for(int j = 0; j < c; j++) {
			if(mask & (1<<j)) {
				ans[0][j] = 1;
				press(0, j);
			}
		}
		if(isOK()) break;
	}
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while(T--) {
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		printf("PUZZLE #%d\n", Case++);
		solve();
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c - 1; j++) printf("%d ", ans[i][j]);
			printf("%d\n", ans[i][c-1]);
		}
	}
	return 0;
}