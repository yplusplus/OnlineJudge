#include <iostream>
#include <cstdio>
using namespace std;
#define MAX 505

struct node {
    int x, y, dir;
    void init(int a, int b, int c) {
        x = a, y = b, dir = c;
    }
} s, t, goal;
int r, c, n, m;
int maz[MAX][MAX][4];
bool visit[MAX][MAX];
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

void dfs(node now, node goal) {
    node next;
    while (1) {
        visit[now.x][now.y] = true;
        if (now.x == goal.x && now.y == goal.y && now.dir == goal.dir) break;
        for (int i = now.dir; i < 4 + now.dir; i++) {
            int index = (now.dir - (i - now.dir) + 4) % 4;
            if (maz[now.x][now.y][(now.dir - (i - now.dir) + 5) % 4] == 0) {
                next.init(now.x + dx[index], now.y + dy[index], (now.dir - (i - now.dir) + 5) % 4);
                now = next;
                break;
            }
        }
    }
}

void init() {
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++) {
			visit[i][j] = false;
			for (int k = 0; k < 4; k++)
				maz[i][j][k] = 1;
		}
		maz[t.x][t.y][s.dir] = maz[s.x][s.y][t.dir] = 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &r, &c);
        scanf("%d%d", &s.y, &t.y);
		s.init(1, s.y + 1, 2), t.init(r, t.y + 1, 0);
        init();
        for (int i = 1; i < 2 * r; i++) {
            if (i % 2 != 0) {
                for (int j = 1; j < c; j++) {
                    scanf("%d", &maz[(i + 1) / 2][j][1]);
                    maz[(i + 1) / 2][j + 1][3] = maz[(i + 1) / 2][j][1];
                }
            } else {
                for (int j = 1; j <= c; j++) {
                    scanf("%d", &maz[i / 2][j][2]);
                    maz[i / 2 + 1][j][0] = maz[i / 2][j][2];
                }
            }
        }
        goal.init(t.x + 1, t.y, s.dir);
        dfs(s, goal);
        goal.init(s.x - 1, s.y, t.dir);
        dfs(t, goal);
        bool flag = false;
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                if (!visit[i][j])
                    flag = true;
        if (!flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}