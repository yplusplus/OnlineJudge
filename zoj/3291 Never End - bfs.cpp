#include "iostream"
#include "queue"
#include "cstdio"
using namespace std;
#define MAX 505
struct node {
	int x, y, dir;
	void init(int a, int b, int c) {
		x = a, y = b, dir = c;
	}
}rot[MAX][MAX][4], s;
int n, m;
int ti[MAX][MAX][4];
char maz[MAX][MAX];
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

bool check(int i, int j) {
	if(i >= 1 && i <= n && j >= 1 && j <= m) return true;
	return false;
}

int bfs() {
	queue<node> que;
	que.push(s);
	ti[s.x][s.y][s.dir] = 1;
	while(!que.empty()) {
		node now = que.front(), next;
		que.pop();
		if(maz[now.x][now.y] == 'E') return ti[now.x][now.y][now.dir];
		for(int i = 0; i < 4; i++) {
			if((now.dir % 2 == 0 && i % 2 != 0) || (now.dir % 2 != 0 && i % 2 == 0)) {
				if(maz[now.x+dx[i]][now.y+dy[i]] != '#') {
					next = rot[now.x+dx[i]][now.y+dy[i]][now.dir];
					if(!ti[next.x][next.y][next.dir]) {
						ti[next.x][next.y][next.dir] = ti[now.x][now.y][now.dir] + 1;
						que.push(next);
					}
				}
			}
			if(i % 2) {
				next = rot[now.x][now.y][(now.dir + i) % 4];
				if(!ti[next.x][next.y][next.dir]) {
					ti[next.x][next.y][next.dir] = ti[now.x][now.y][now.dir] + 1;
					que.push(next);
				}
			}
		}
	}
	return 0;
}

void init() {
	for(int i = n; i; i--)
		for(int j = m; j; j--)
			if(maz[i][j] != '#') {
				if(check(i + 1, j) && maz[i+1][j] != '#') rot[i][j][0] = rot[i+1][j][0];
				else rot[i][j][0].init(i, j, 0);
				if(check(i, j + 1) && maz[i][j+1] != '#') rot[i][j][3] = rot[i][j+1][3];
				else rot[i][j][3].init(i, j, 3);
			}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(maz[i][j] != '#') {
				if(check(i - 1, j) && maz[i-1][j] != '#') rot[i][j][2] = rot[i-1][j][2];
				else rot[i][j][2].init(i, j, 2);
				if(check(i, j - 1) && maz[i][j-1] != '#') rot[i][j][1] = rot[i][j-1][1];
				else rot[i][j][1].init(i, j, 1);
			}
}

int main() {
	while(~scanf("%d%d", &n, &m)) {
		getchar();
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m + 1; j++) {
				for(int k = 0; k < 4; k++) ti[i][j][k] = 0;
				scanf("%c", &maz[i][j]);
				if(maz[i][j] == '|') s.init(i, j, 0);
			}
		init();
		int ans = bfs();
		if(!ans) printf("Can not escape!\n");
		else printf("%d\n", ans - 1);
	}
	return 0;
}