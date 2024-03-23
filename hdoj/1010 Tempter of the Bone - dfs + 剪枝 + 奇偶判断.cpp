#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

char maz[10][10];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};
int n, m, t;
int sx, sy, tx, ty;
bool visit[10][10];
bool check(int x, int y) {
    if(x >= 0 && x < n && y >= 0 && y < m) return true;
    return false;
}

bool dfs(int x, int y, int dep) {
    if(dep == t) {
        if(x == tx && y == ty) return true;
        return false;
    }
    if(x == tx && y == ty) return false;
    for(int i = 0; i < 4; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if(check(xx, yy) && maz[xx][yy] != 'X' && !visit[xx][yy]) {
            visit[xx][yy] = true;
            if(dfs(xx, yy, dep + 1)) return true;
            visit[xx][yy] = false;
        }
    }
    return false;
}

int main() {
    while(~scanf("%d%d%d", &n, &m, &t), n + m + t) {
        for(int i = 0; i < n; i++) {
            scanf("%s", maz[i]);
            for(int j = 0; j < m; j++) {
                if(maz[i][j] == 'S') sx = i, sy = j;
                else if(maz[i][j] == 'D') tx = i, ty = j;
            }
        }
        int res = abs(sx - tx) + abs(sy - ty);
        if(((res & 1) ^ (t & 1)) || n * m < t) {
            puts("NO");
            continue;
        }
        memset(visit, false, sizeof(visit));
        visit[sx][sy] = true;
        if(dfs(sx, sy, 0)) puts("YES");
        else puts("NO");
    }
    return 0;
}
