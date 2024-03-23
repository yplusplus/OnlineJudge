#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};
char maz[105][105];
bool visit[105][105];
int r, c, ans, tot;
int path[105][105][3];
struct pos {
	int x, y, time;
	pos() {};
	pos(int a, int b, int c) {
		x = a, y = b, time = c;
	}
	bool operator< (const pos & a) const {
		return time > a.time;
	}
};

bool check(int x, int y) {
	return x >= 0 && x < r && y >= 0 && y < c && maz[x][y] != 'X';
}

int bfs() {
	memset(visit, false, sizeof(visit));
	memset(path, 0, sizeof(path));
	priority_queue<pos> que;
	que.push(pos(0, 0, 0));
	visit[0][0] = true;
	while(!que.empty()) {
		pos now = que.top();
		que.pop();
		if(now.x == r - 1 && now.y == c - 1) return now.time;
		for(int i = 0; i < 4; i++) {
			int nx = now.x + dx[i], ny = now.y + dy[i];
			if(!check(nx, ny) || visit[nx][ny]) continue;
			if(maz[nx][ny] == '.') que.push(pos(nx, ny, now.time + 1));
			else {
				int t = maz[nx][ny] - '0' + 1;
				que.push(pos(nx, ny, now.time + t));
				path[nx][ny][0] = t;
			}
			path[nx][ny][1] = now.x;
			path[nx][ny][2] = now.y;
			visit[nx][ny] = true;
		}
	}
	return -1;
}

void dfs(int x, int y) {
	int xx = path[x][y][1], yy = path[x][y][2];
	if(path[x][y][1] != 0 || path[x][y][2] != 0) dfs(xx, yy);
	if(!path[x][y][0]) printf("%ds:(%d,%d)->(%d,%d)\n", tot++, xx, yy, x, y);
	else {
		printf("%ds:(%d,%d)->(%d,%d)\n", tot++, xx, yy, x, y);
		for(int i = 1; i < path[x][y][0]; i++) {
			printf("%ds:FIGHT AT (%d,%d)\n", tot++, x, y);
		}
	}
}

	
int main() {
	while(~scanf("%d%d", &r, &c)) {
		getchar();
		for(int i = 0; i < r; i++) {
			for(int j = 0; j <= c; j++) {
				maz[i][j] = getchar();
			}
		}
		ans = bfs();
		if(ans == -1) printf("God please help our poor hero.\nFINISH\n");
		else {
			printf("It takes %d seconds to reach the target position, let me show you the way.\n", ans);
			tot = 1, dfs(r - 1, c - 1);
			printf("FINISH\n");
		}
	}
	return 0;
}