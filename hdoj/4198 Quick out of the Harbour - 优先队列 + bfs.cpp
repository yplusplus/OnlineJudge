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
int h, w, d;
int sx, sy;
char maz[510][510];
int dx[] = {0, 0, 1, -1};
int dy[]=  {-1, 1, 0, 0};
bool visit[510][510];
struct Node {
    int x, y, ti;
    Node(){}
    Node(int _x, int _y, int _ti) {
        x = _x, y = _y, ti = _ti;
    }
    bool operator<(const Node &x) const {
        return ti > x.ti;
    }
};

bool check(int x, int y) {
    if(x >= 1 && x <= h && y >= 1 && y <= w) return true;
    return false;
}

void bfs() {
    int ans;
    memset(visit, false, sizeof(visit));
    priority_queue<Node> que;
    que.push(Node(sx, sy, 1));
    while(!que.empty()) {
        Node now = que.top();
        que.pop();
        if(visit[now.x][now.y]) continue;
        else visit[now.x][now.y] = true;
        if((now.x == 1 || now.x == h) || (now.y == 1 || now.y == w)) {
            ans = now.ti;
            break;
        }
        for(int i = 0; i < 4; i++) {
            int nx = now.x + dx[i], ny = now.y + dy[i];
            if(!check(nx, ny) || maz[nx][ny] == '#' || visit[nx][ny]) continue;
            if(maz[nx][ny] == '@') que.push(Node(nx, ny, now.ti + d + 1));
            else que.push(Node(nx, ny, now.ti + 1));
        }
    }
    cout << ans << endl;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &h, &w, &d);
        for(int i = 1; i <= h; i++) {
            scanf("%s", &maz[i][1]);
        }
        for(int i = 1; i <= h; i++) {
            for(int j = 1; j <= w; j++) {
                if(maz[i][j] == 'S') sx = i, sy = j;
            }
        }
        bfs();
    }
    return 0;
}
