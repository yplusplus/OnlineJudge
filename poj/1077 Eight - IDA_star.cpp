#include "iostream"
#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "queue"
using namespace std;
#define SIZE 3
char board[4][4];
const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, -1, 1, 0};
char op[] = {'u', 'l', 'r', 'd'};
int goal_state[10][2] = {{0,0}, {1,1}, {1,2}, {1,3}, {2,1}, {2,2}, {2,3}, {3,1}, {3,2}, {3,3}};
int bound;
bool flag;
char solution[1000];
//估价函数
int h(char board[][4]) {
	int cost = 0;
	for(int i = 1; i <= SIZE; i++) {
		for(int j = 1; j <= SIZE; j++) {
			if(board[i][j] != 9) {
				cost += abs(i - goal_state[board[i][j]][0]) + abs(j - goal_state[board[i][j]][1]);
			}
		}
	}
	return cost;
}

bool check(int x, int y) {
	if(x >= 1 && x <= SIZE && y >= 1 && y <= SIZE) return true;
	return false;
}

int dfs(int x, int y, int dv, char pre) {
	int hv = h(board);
	if(hv + dv > bound) return hv + dv;
	if(hv == 0) {
		flag = true;
		return dv;
	}
	int next_bound = 1e9;
	for(int i = 0; i < 4; i++) {
		if(i + pre == 3) continue;//与上一步相反的移动
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(check(nx, ny)) {
			solution[dv] = i;
			swap(board[x][y], board[nx][ny]);
			int new_bound = dfs(nx, ny, dv + 1, i);
			if(flag) return new_bound;
			next_bound = min(new_bound, next_bound);
			swap(board[x][y], board[nx][ny]);
		}
	}
	return next_bound;
}
		
void IDA_star(int sx, int sy) {
	flag = false;
	bound = h(board);
	while(!flag && bound <= 100) {
		bound = dfs(sx, sy, 0, -10);
	}
}

int main() {
	int sx, sy;
	char c[2];
	for(int i = 1; i <= SIZE; i++) {
		for(int j = 1; j <= SIZE; j++) {
			scanf("%s", c);
			if(c[0] == 'x') {
				board[i][j] = 9;
				sx = i, sy = j;
			} else board[i][j] = c[0] - '0';
		}
	}
	IDA_star(sx, sy);
	if(flag) for(int i = 0; i <bound; i++) printf("%c", op[solution[i]]);
	else printf("unsolvable\n");
	return 0;
}
