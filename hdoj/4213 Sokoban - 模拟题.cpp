#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int n, m;
char op[100];
char maz[20][20];
int g[20][20];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int sx, sy;

bool check() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (maz[i][j] == 'b') return false;
    return true;
}

void go(int x, int y, int idx) {

    int xx = x + dx[idx], yy = y + dy[idx];
    int xxx = xx + dx[idx], yyy = yy + dy[idx];
    if (maz[xx][yy] == '#') return;
    if (maz[x][y] == 'W') {
        if (maz[xx][yy] == '.') {
            maz[x][y] = '+', maz[xx][yy] = 'w';
            sx = xx, sy = yy;
        } else if (maz[xx][yy] == '+') {
            swap(maz[x][y], maz[xx][yy]);
            sx = xx, sy = yy;
        } else if (maz[xx][yy] == 'b') {
            if (maz[xxx][yyy] == '.') {
                maz[x][y] = '+';
                maz[xx][yy] = 'w';
                maz[xxx][yyy] = 'b';
                sx = xx, sy = yy;
            } else if (maz[xxx][yyy] == '+') {
                maz[x][y] = '+';
                maz[xx][yy] = 'w';
                maz[xxx][yyy] = 'B';
                sx = xx, sy = yy;
            }
        } else if (maz[xx][yy] == 'B') {
            if (maz[xxx][yyy] == '.') {
                maz[x][y] = '+';
                maz[xx][yy] = 'W';
                maz[xxx][yyy] = 'b';
                sx = xx, sy = yy;
            } else if (maz[xxx][yyy] == '+') {
                maz[x][y] = '+';
                maz[xx][yy] = 'W';
                maz[xxx][yyy] = 'B';
                sx = xx, sy = yy;
            }
        }
    } else {
        if (maz[xx][yy] == '.') {
            maz[x][y] = '.', maz[xx][yy] = 'w';
            sx = xx, sy = yy;
        } else if (maz[xx][yy] == '+') {
            maz[x][y] = '.';
            maz[xx][yy] = 'W';
            sx = xx, sy = yy;
        } else if (maz[xx][yy] == 'b') {
            if (maz[xxx][yyy] == '.') {
                maz[x][y] = '.';
                maz[xx][yy] = 'w';
                maz[xxx][yyy] = 'b';
                sx = xx, sy = yy;
            } else if (maz[xxx][yyy] == '+') {
                maz[x][y] = '.';
                maz[xx][yy] = 'w';
                maz[xxx][yyy] = 'B';
                sx = xx, sy = yy;
            }
        } else if (maz[xx][yy] == 'B') {
            if (maz[xxx][yyy] == '.') {
                maz[x][y] = '.';
                maz[xx][yy] = 'W';
                maz[xxx][yyy] = 'b';
                sx = xx, sy = yy;
            } else if (maz[xxx][yyy] == '+') {
                maz[x][y] = '.';
                maz[xx][yy] = 'W';
                maz[xxx][yyy] = 'B';
                sx = xx, sy = yy;
            }
        }
    }
}

void solve() {
    int opcnt = strlen(op);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (maz[i][j] == 'w' || maz[i][j] == 'W') sx = i, sy = j;
        }
    }
    int len = strlen(op);
    for (int i = 0; i < len; i++) {
        if(check()) break;
        switch (op[i]) {
            case 'U':go(sx, sy, 0);
                break;
            case 'D':go(sx, sy, 1);
                break;
            case 'L':go(sx, sy, 2);
                break;
            case 'R':go(sx, sy, 3);
                break;
        }
    }
    if(check()) printf("complete\n");
    else printf("incomplete\n");
    for (int i = 1; i <= n; i++)
        printf("%s\n", &maz[i][1]);
}

int main() {
    int Case = 1;
    while (~scanf("%d%d", &n, &m)) {
        if (!n && !m) break;
        for (int i = 1; i <= n; i++) {
            scanf("%s", &maz[i][1]);
        }
        scanf("%s", op);
        printf("Game %d: ", Case++);
        solve();
    }
    return 0;
}

