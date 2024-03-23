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
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 510
const int inf = 1 << 30;
int n, m;
int maz[maxn][maxn];
bool visit[maxn][maxn];
int ans[maxn*maxn];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int cnt;

struct Node {
    int x, y, t, ti;
    Node(){}
    Node(int _x, int _y, int _t, int _ti) {
        x = _x, y = _y, t = _t, ti = _ti;
    }
    bool operator <(const Node &x) const {
        if(ti == x.ti) return t > x.t;
        return ti > x.ti;
    }
};

bool check(int x, int y) {
    if(x >= 1 && x <= n && y >= 1 && y <= m) return true;
    return false;
}

void bfs() {
    priority_queue<Node> que;
    memset(visit, false, sizeof(visit));
    memset(ans, 0, sizeof(ans));
    cnt = n * m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d", &maz[i][j]);
            if(maz[i][j] > 0) {
                cnt--;
                que.push(Node(i, j, maz[i][j], 1));
                visit[i][j] = true;
                ans[maz[i][j]]++;
            }
        }
    }
    while(!que.empty() && cnt) {
        Node now = que.top();
        que.pop();
        for(int i = 0; i < 4; i++) {
            int xx = now.x + dx[i], yy = now.y + dy[i];
            if(!check(xx, yy) || visit[xx][yy]) continue;
            if(maz[xx][yy] + now.ti < 0) {
                que.push(Node(now.x, now.y, now.t, -maz[xx][yy]));
            } else {
                ans[now.t]++;
                visit[xx][yy] = true;
                cnt--;
                que.push(Node(xx, yy, now.t, now.ti));
            }
        }
    }
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        bfs();
        int x, q;
        scanf("%d", &q);
        while(q--) {
            scanf("%d", &x);
            printf("%d\n", ans[x]);
        }
    }
    return 0;
}
