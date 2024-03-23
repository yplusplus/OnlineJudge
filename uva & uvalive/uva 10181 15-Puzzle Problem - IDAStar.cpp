#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int inf = 1 << 30;
const int N = 4;

const int target_pos[N * N][2] = {
    {3, 3}, {0, 0}, {0, 1}, {0, 2},
    {0, 3}, {1, 0}, {1, 1}, {1, 2},
    {1, 3}, {2, 0}, {2, 1}, {2, 2},
    {2, 3}, {3, 0}, {3, 1}, {3, 2}
};


bool check(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}
    
int h(int board[][N]) {
    int res = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int num = board[i][j];
            if (num) res += abs(target_pos[num][0] - i) + abs(target_pos[num][1] - j);
        }
    }
    return res;
}

bool can_be_solved(int board[][N]) {
    int a[N * N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i * N + j] = board[i][j];
        }
    }
    int res = 0;
    for (int i = 0; i < N * N; i++) {
        if (a[i] == 0) res += i >> 2;
        else {
            for (int j = 0; j < i; j++) res += a[j] > a[i];
        }
    }
    return res & 1;
}

int board[N][N];
int dx[] = {0, -1, 1, 0};
int dy[] = {1, 0, 0, -1};
char move[] = "RUDL";
char moves[1111];
int limit, next_limit;

int get_moveId(char ch) {
    switch (ch) {
        case 'R': return 0;
        case 'U': return 1;
        case 'D': return 2;
        case 'L': return 3;
    }
    return -1;
}

void display_board(int board[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
            //cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool dfs(int x, int y, int pre, int depth) {
    moves[depth] = 0;
    int value = h(board);
    if (depth + value > limit) {
        next_limit = min(next_limit, depth + value);
        return false;
    }
    if (!value) {
        return true;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (check(nx, ny) && i + pre != 3) {
            swap(board[x][y], board[nx][ny]);
            moves[depth] = move[i];
            if (dfs(nx, ny, i, depth + 1)) return true;
            swap(board[x][y], board[nx][ny]);
        }
    }
    return false;
}

int IDA_star(int x, int y) {
    for (limit = 0, next_limit = inf; !dfs(x, y, -1, 0); limit = next_limit, next_limit = inf) {
    }
    return limit;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int x, y;
        //int init_board[N][N];
        //printf("输入一个15数码：\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> board[i][j];
                if (!board[i][j]) x = i, y = j;
            }
        }
        //getchar();
        //memcpy(init_board, board, sizeof(board));
        if (can_be_solved(board)) {
            int number_of_steps = IDA_star(x, y);
            puts(moves);
            /*
            printf("一共 %d 步：%s\n", number_of_steps, moves);
            for (int i = 0; i < number_of_steps; i++) {
                printf("回车显示第 %d 步\n", i + 1);
                getchar();
                int moveId = get_moveId(moves[i]);
                int nx = x + dx[moveId], ny = y + dy[moveId];
                swap(init_board[x][y], init_board[nx][ny]);
                display_board(init_board);
                x = nx, y = ny;
            }
            */
        } else {
            puts("This puzzle is not solvable.");
            //puts("这个十五数码无解");
        }
    }
    return 0;
}
