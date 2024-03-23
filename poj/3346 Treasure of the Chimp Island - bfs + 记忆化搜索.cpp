#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 30;
char maz[110][110];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int r, c, ans;
int visit[110][110][30];
struct Node {
    int x, y, d;
    Node(){}
    Node(int _x, int _y, int _d) {
        x = _x, y = _y, d = _d;
    }
};

Node q[1000000];
int head, tail;
bool check(int x, int y) {
    if(x >= 0 && x < r && y >= 0 && y < c) return true;
    return false;
}

void bfs(int sx, int sy) {
    int sd = 0;
	if(maz[sx][sy] != '#') sd = maz[sx][sy] - 'A' + 1;
    visit[sx][sy][sd] = 0;
    head = tail = 0;
    q[tail++] = Node(sx, sy, sd);
    while(head < tail) {
        Node now = q[head++];
        if(maz[now.x][now.y] == '$') {
			ans = min(ans, visit[now.x][now.y][now.d]);
			continue;
		}
        if(visit[now.x][now.y][now.d] >= ans) continue;
        for(int i = 0; i < 4; i++) {
            int nx = now.x + dx[i], ny = now.y + dy[i];
            if(!check(nx, ny) || maz[nx][ny] == '*') continue;
            if(isdigit(maz[nx][ny])) {//isblock
                if(now.d) {
                    int tmp = visit[now.x][now.y][now.d];
                    if(visit[nx][ny][now.d-1] > tmp) {
                        visit[nx][ny][now.d-1] = tmp;
                        q[tail++] = Node(nx, ny, now.d-1);
                    }
				}
				int tmp = visit[now.x][now.y][now.d] + maz[nx][ny] - '0';
				if(visit[nx][ny][now.d] > tmp) {
					visit[nx][ny][now.d] = tmp;
                        q[tail++] = Node(nx, ny, now.d);
				}
            } else if(maz[nx][ny] == '.' || maz[nx][ny] == '$') {//isn'tblock
                if(visit[nx][ny][now.d] > visit[now.x][now.y][now.d]) {
                    visit[nx][ny][now.d] = visit[now.x][now.y][now.d];
                    q[tail++] = Node(nx, ny, now.d);
                }
            }
        }
    }
}

int main() {
    while(1) {
        r = 0;
        while(gets(maz[r])) {
            if(strlen(maz[r]) < 1) break;
            if(strcmp(maz[0], "--") == 0) return 0;
            r++;
        }
        c = strlen(maz[0]);
        ans = inf;
        fill(&visit[0][0][0], &visit[110][110][30], inf);
        for(int i = 0; i < r; i++) {
			if(isupper(maz[i][0]) || maz[i][0] == '#') bfs(i, 0);
            if(isupper(maz[i][c-1]) || maz[i][c-1] == '#') bfs(i, c-1);
        }
        for(int i = 0; i < c; i++) {
            if(isupper(maz[0][i]) || maz[0][i] == '#') bfs(0, i);
            if(isupper(maz[r-1][i]) || maz[r-1][i] == '#') bfs(r-1, i);
        }
        if(ans == inf) printf("IMPOSSIBLE\n");
        else printf("%d\n", ans);
    }
    return 0;
}
