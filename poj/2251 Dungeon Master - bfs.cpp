#include "iostream"
#include "queue"
#include "cstdio"
#include "cstring"
using namespace std;
#define MAX 35
char maz[MAX][MAX][MAX];
int time[MAX][MAX][MAX];
int l, r, c;
int dx[] = {0, 0, 0, 0, 1, -1};
int dy[] = {0, 1, 0, -1, 0, 0};
int dz[] = {1, 0, -1, 0, 0, 0};

typedef struct node {
	int x, y, z;
}node;
node s, e;
void bfs() {
	queue<node> que;
	que.push(s);
	time[s.x][s.y][s.z] = 1;
	while(!que.empty()) {
		node tmp, now = que.front();
		que.pop();
		if(now.x == e.x && now.y == e.y && now.z == e.z) break;
		for(int i = 0; i < 6; i++) {
			tmp.x = now.x + dx[i];
			tmp.y = now.y + dy[i];
			tmp.z = now.z + dz[i];
			if(tmp.x >= 0 && tmp.x < l && tmp.y >= 0 && tmp.y < r && tmp.z >= 0 && tmp.z < c && !time[tmp.x][tmp.y][tmp.z] && maz[tmp.x][tmp.y][tmp.z] != '#') {
				time[tmp.x][tmp.y][tmp.z] = time[now.x][now.y][now.z] + 1;
				que.push(tmp);
			}
		}
	}
}
int main() {
	while(1) {
		scanf("%d%d%d\n", &l, &r, &c);
		if(!l && !r && !c) break;
		char ch;
		for(int i = 0; i < l; i++) {
			for(int j = 0; j < r; j++) {
				for(int k = 0; k <= c; k++) {
					scanf("%c", &maz[i][j][k]);
					time[i][j][k] = 0;
					if(maz[i][j][k] == 'S') s.x = i, s.y = j, s.z = k;
					if(maz[i][j][k] == 'E') e.x = i, e.y = j, e.z = k;
				}
			}
			ch = getchar();
		}
		bfs();
		if(time[e.x][e.y][e.z]) printf("Escaped in %d minute(s).\n", time[e.x][e.y][e.z] - 1);
		else printf("Trapped!\n");
	}
	return 0;
}