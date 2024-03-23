#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
int r, c, sx, sy;
int cnt;
char maz[20][20];
int maze[20][20];
bool visit[20][20][40000];
int dir[][2] = {0, 1, 1, 0, -1, 0, 0, -1, 1, -1, -1, 1, 1, 1, -1, -1};
int kdir[][2] = {-2, -1, -2, 1, 2, 1, 2, -1, 1, 2, 1, -2, -1, 2, -1, -2};
int bdir[][2] = {1, -1, 1, 1, -1, -1, -1, 1};
int rdir[][2] = {0, 1, 1, 0, -1, 0, 0, -1};
struct Node {
	int x, y, ti, mask;
	Node(){}
	Node(int _x, int _y, int _ti, int _mask) {
		x = _x, y = _y, ti = _ti, mask = _mask;
	}
};

struct Piece {
	int x, y, type;
	Piece(){}
	Piece(int _x, int _y, int _type) {
		x = _x, y = _y, type = _type;
	}
}p[20];

bool check(int x, int y) {
	if(x >= 1 && x <= r && y >= 1 && y <= c) return true;
	return false;
}

bool IsEat(int x, int y, int mask) {
	//Knight
	for(int i = 0; i < 8; i++) {
		int xx = x + kdir[i][0], yy = y + kdir[i][1];
		int tmp = maze[xx][yy];
		if(!check(xx, yy)) continue;
		if(tmp >= 0 && !(mask & (1 << tmp)) && p[tmp].type == 0) return true;
	}
	//Bishop
	for(int i = 0; i < 4; i++) {
		int xx = x + bdir[i][0], yy = y + bdir[i][1];
		int tmp = maze[xx][yy];
		while(check(xx, yy)) {
			if(tmp >= 0 && !(mask & (1 << tmp))) {
				if(p[tmp].type == 1) return true;
				else break;
			} else xx += bdir[i][0], yy += bdir[i][1], tmp = maze[xx][yy];
		}
	}
	//Rook
	for(int i = 0; i < 4; i++) {
		int xx = x + rdir[i][0], yy = y + rdir[i][1];
		int tmp = maze[xx][yy];
		while(check(xx, yy)) {
			if(tmp >= 0 && !(mask & (1 << tmp))) {
				if(p[tmp].type == 2) return true;
				else break;
			} else xx += rdir[i][0], yy += rdir[i][1], tmp = maze[xx][yy];
		}
	}
	return false;
}

int bfs() {
	queue<Node> que;
	memset(visit, false, sizeof(visit));
	visit[sx][sy][0] = true;
	que.push(Node(sx, sy, 0, 0));
	while(!que.empty()) {
		Node now = que.front();
		que.pop();
		if(now.mask == (1 << cnt) - 1) return now.ti;
		for(int i = 0; i < 8; i++) {
			int nx = now.x + dir[i][0], ny = now.y + dir[i][1], mask = now.mask;
			if(!check(nx, ny)) continue;
			int tmp = maze[nx][ny];
			if(tmp >= 0) mask |= (1 << tmp);
			if(visit[nx][ny][mask]) continue;
			if(IsEat(nx, ny, mask)) continue;
			que.push(Node(nx, ny, now.ti + 1, mask));
			visit[nx][ny][mask] = true;
		}
	}
	return -1;
}

int main() {
	while(~scanf("%d%d", &r, &c)) {
		cnt = 0;
		memset(maze, -1, sizeof(maze));
		for(int i = 1; i <= r; i++) scanf("%s", &maz[i][1]);
		for(int i = 1; i <= r; i++) {
			for(int j = 1; j <= c; j++) {
				if(maz[i][j] == '.') continue;
				if(maz[i][j] == '*') sx = i, sy = j;
				else if(maz[i][j] == 'K') {
					maze[i][j] = cnt, p[cnt++] = Piece(i, j, 0);
				} else if(maz[i][j] == 'B') {
					maze[i][j] = cnt, p[cnt++] = Piece(i, j, 1);
				} else maze[i][j] = cnt, p[cnt++] = Piece(i, j, 2);
			}
		}
		int ans = bfs();
		cout << ans << endl;
	}
	return 0;
}