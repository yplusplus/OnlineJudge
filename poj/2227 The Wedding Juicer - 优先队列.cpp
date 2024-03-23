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
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

struct Node {
    ll h;
    int x, y;
    Node(){}
    Node(ll _h, int _x, int _y) {
        h = _h, x = _x, y = _y;
    }
    bool operator <(const Node &a) const {
        return h > a.h;
    }
};

ll maz[305][305];
int r, c;
bool visit[305][305];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool check(int x, int y) {
    if(x > 0 && x <= r && y > 0 && y <= c) return true;
    return false;
}

void solve() {
    ll ans = 0;
    priority_queue<Node> que;
    memset(visit, false, sizeof(visit));
    for(int j = 1; j <= c; j++) que.push(Node(maz[1][j], 1, j)), visit[1][j] = true, visit[0][j] = true;
    for(int j = 1; j <= c; j++) que.push(Node(maz[r][j], r, j)), visit[r][j] = true, visit[r+1][j] = true;
    for(int i = 2; i < r; i++) {
        que.push(Node(maz[i][1], i, 1));
        visit[i][1] = true, visit[i][0] = true;
        que.push(Node(maz[i][c], i , c));
        visit[i][c] = true, visit[i][c+1] = true;
    }
    while(!que.empty()) {
        Node now = que.top();
        que.pop();
        for(int i = 0; i < 4; i++) {
            int nx = now.x + dx[i];
            int ny = now.y + dy[i];
            if(!visit[nx][ny] && check(nx, ny)) {
				if(maz[nx][ny] < now.h) {
                    ans += now.h - maz[nx][ny];
					que.push(Node(now.h, nx, ny));
                } else que.push(Node(maz[nx][ny], nx, ny));
                visit[nx][ny] = true;
            }
        }
    }
    printf("%lld\n", ans);
}

int main() {
    while(~scanf("%d%d", &c, &r)) {
        for(int i = 1; i <= r; i++) {
            for(int j = 1; j <= c; j++) {
                scanf("%lld", &maz[i][j]);
            }
        }
        solve();
    }
    return 0;
}
