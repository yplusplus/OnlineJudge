#include "iostream"
#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "queue"
using namespace std;
#define SIZE 3
const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, -1, 1, 0};
char op[] = {'u', 'l', 'r', 'd'};
int goal_state[10][2] = {{0,0}, {1,1}, {1,2}, {1,3}, {2,1}, {2,2}, {2,3}, {3,1}, {3,2}, {3,3}};
int bound;
char a[10];
bool flag;
char solution[1000];

struct Eight {
    char board[4][4];
    int x, y;
};

int h(char board[][4]) {
    int cost = 0;
    for(int i = 1; i <= SIZE; i++)
        for(int j = 1; j <= SIZE; j++)
            if(board[i][j]) cost += abs(i - goal_state[board[i][j]][0]) + abs(j - goal_state[board[i][j]][1]);
    return cost;
}

bool solvable() {
	int cnt = 0;
	for(int i = 1; i <= 9; i++)
		for(int j = 1; j < i; j++)
			if(a[j] < a[i] && a[j]) cnt++;
	if(cnt & 1) return false;
	return true;
}

bool check(int x, int y) {
    if(x >= 1 && x <= SIZE && y >= 1 && y <= SIZE) return true;
    return false;
}

bool dfs(Eight now, int dv, char pre) {
    if(h(now.board) == 0) {
        solution[dv] = 0;
        return true;
    }
    for(int i = 0; i < 4; i++) {
        if(i + pre == 3) continue;//与上一步相反的移动
        Eight next = now;
        next.x += dx[i], next.y += dy[i];
        if(check(next.x, next.y)) {
            solution[dv] = op[i];
            swap(next.board[next.x][next.y], next.board[now.x][now.y]);
            if(h(next.board) + dv >= bound) continue;
            if(dfs(next, dv + 1, i)) return true;
        }
    }
    return false;
}
        
void IDA_star(Eight st) {
	bound = h(st.board);
	for(bound = h(st.board); !dfs(st, 0, -10); bound++);
    puts(solution);
}

int main() {
    int sx, sy;
    char c[2];
    while(1) {
        Eight st;
        for(int i = 1; i <= SIZE; i++) {
            for(int j = 1; j <= SIZE; j++) {
                if(scanf("%s", c) == EOF) return 0;
                if(c[0] == 'x') {
                    st.board[i][j] = 0;
                    st.x = i, st.y = j;
                } else st.board[i][j] = c[0] - '0';
				a[(i - 1) * SIZE + j] = st.board[i][j];
            }
        }
		if(solvable()) IDA_star(st);
		else printf("unsolvable\n");
    }
    return 0;
}
