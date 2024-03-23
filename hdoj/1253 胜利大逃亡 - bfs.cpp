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
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 55;
int a, b, c, limit;
int reachTime[N][N][N];
int maz[N][N][N];
int dx[] = {0, 0, 0, 0, -1, 1};
int dy[] = {1, -1, 0, 0, 0, 0};
int dz[] = {0, 0, -1, 1, 0, 0};

bool check(int x, int y, int z) {
    return x >= 0 && x < a && y >= 0 && y < b && z >= 0 && z < c && maz[x][y][z] == 0;
}
int bfs() {
    queue<int> que;
    int x, y, z;
    que.push(0);
    que.push(0);
    que.push(0);
    reachTime[0][0][0] = 0;
    while (!que.empty()) {
        x = que.front(), que.pop();
        y = que.front(), que.pop();
        z = que.front(), que.pop();
        for (int i = 0; i < 6; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nz = z + dz[i];
            if (check(nx, ny, nz) && reachTime[nx][ny][nz] == inf) {
                que.push(nx), que.push(ny), que.push(nz);
                reachTime[nx][ny][nz] = reachTime[x][y][z] + 1;
            }
        }
    }
    int minTime = reachTime[a-1][b-1][c-1];
    if (minTime <= limit) {
        return minTime;
    } else {
        return -1;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &a, &b, &c, &limit);
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                for (int k = 0; k < c; k++) {
                    scanf("%d", &maz[i][j][k]);
                    reachTime[i][j][k] = inf;
                }
            }
        }
        printf("%d\n", bfs());
    }
    return 0;
}
