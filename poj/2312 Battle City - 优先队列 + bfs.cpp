#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
int r, c, sx, sy;
int maz[305][305];
bool visit[305][305];
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
	return x >= 0 && x < r && y >= 0 && y < c;
}

int bfs() {
	memset(visit, false, sizeof(visit));
	priority_queue<pos> que;
	que.push(pos(sx, sy, 0));
	while(!que.empty()) {
		pos now = que.top();
		que.pop();
		if(maz[now.x][now.y] == 'T') return now.time;
		if(!visit[now.x][now.y]) {
			visit[now.x][now.y] = true;
			for(int i = 0; i < 4; i++) {
				int nx = now.x + dx[i];
				int ny = now.y + dy[i];
				if(!check(nx, ny) || maz[nx][ny] == 'S' || maz[nx][ny] == 'R' || visit[nx][ny]) continue;
				if(maz[nx][ny] == 'B') que.push(pos(nx, ny, now.time + 2));
				else que.push(pos(nx, ny, now.time + 1));
			}
		}
	}
	return -1;
}

int main() {
	while(~scanf("%d%d", &r, &c)) {
		getchar();
		if(!r && !c) break;
		for(int i = 0; i < r; i++) {
			for(int j = 0; j <= c; j++) {
				scanf("%c", &maz[i][j]);
				if(maz[i][j] == 'Y') sx = i, sy = j;
			}
		}
		printf("%d\n", bfs());
	}
	return 0;
}