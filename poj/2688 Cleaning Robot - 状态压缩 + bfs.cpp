#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
const int M = 22;
char maz[M][M];
int dis[M][M][1 << 10];
int id[M][M];
int w, h;
int dirtys = 0;

bool inmaz(int x, int y) { return x >= 0 && x < w && y >= 0 && y < h; }

int bfs(int sx, int sy) {
    memset(dis, -1, sizeof(dis));
    dis[sx][sy][0] = 0;
    queue<int> que;
    que.push(sx);
    que.push(sy);
    que.push(0);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        int y = que.front(); que.pop();
        int mask = que.front(); que.pop();
        if ((mask == (1 << dirtys) - 1)) {
            return dis[x][y][mask];
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!inmaz(nx, ny) || maz[nx][ny] == 'x') continue;
            int nmask = mask;
            if (id[nx][ny] != -1) {
                nmask |= 1 << id[nx][ny];
            }
            if (dis[nx][ny][nmask] == -1) {
                que.push(nx);
                que.push(ny);
                que.push(nmask);
                dis[nx][ny][nmask] = dis[x][y][mask] + 1;
            }
        }
    }
    return -1;
}

void solve() {
    dirtys = 0;
    memset(id, -1, sizeof(id));
    int sx, sy;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (maz[i][j] == 'o') {
                sx = i, sy = j;
            } else if (maz[i][j] == '*') {
                id[i][j] = dirtys++;
            }
        }
    }
    int ans = bfs(sx, sy);
    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d%d", &h, &w), h && w) {
        for (int i = 0; i < w; i++) {
            scanf("%s", maz[i]);
        }
        solve();
    }
    return 0;
}
