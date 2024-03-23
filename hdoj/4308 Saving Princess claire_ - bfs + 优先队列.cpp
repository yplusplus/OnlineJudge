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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define MAX 5050
int r, c, cost, tot;
char maz[MAX][MAX];
int sx, sy, tx, ty;
pii p[300000];
bool visit[MAX][MAX];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

struct State {
    int x, y;
    ll cost;
    State(){}
    State(int _x, int _y, ll _cost) {
        x = _x, y = _y, cost = _cost;
    }
    bool operator<(const State &x) const {
        return cost > x.cost;
    }
};

bool check(int x, int y) {
    if(x >= 0 && x < r && y >= 0 && y < c) return true;
    return false;
}

int bfs() {
    priority_queue<State> que;
    memset(visit, false, sizeof(visit));
    que.push(State(sx, sy, 0));
    bool inP = false;
    while(!que.empty()) {
        State now = que.top();
        que.pop();
        if(now.x == tx && now.y == ty) return now.cost;
        if(visit[now.x][now.y]) continue;
        else visit[now.x][now.y] = true;
        for(int i = 0; i < 4; i++) {
            int xx = now.x + dx[i], yy = now.y + dy[i];
            if(!check(xx, yy) || maz[xx][yy] == '#') continue;
            if(visit[xx][yy]) continue;
            if(maz[xx][yy] == '*') que.push(State(xx, yy, now.cost + cost));
            else que.push(State(xx, yy, now.cost));
        }
        if(maz[now.x][now.y] == 'P') {
            for(int i = 0; i < tot; i++) {
                que.push(State(p[i].fi, p[i].se, now.cost));
            }
        }
    }
    return -1;
}
int main() {
    while(~scanf("%d%d%d", &r, &c, &cost)) {
        tot = 0;
        for(int i = 0; i < r; i++) {
            scanf("%s", &maz[i]);
            for(int j = 0; j < c; j++) {
                if(maz[i][j] == 'Y') sx = i, sy = j;
                if(maz[i][j] == 'C') tx = i, ty = j;
                if(maz[i][j] == 'P') p[tot++] = mp(i, j);
            }
        }
        ll ans = bfs();
        if(ans == -1) puts("Damn teoy!");
        else cout << ans << endl;
    }
    return 0;
}
