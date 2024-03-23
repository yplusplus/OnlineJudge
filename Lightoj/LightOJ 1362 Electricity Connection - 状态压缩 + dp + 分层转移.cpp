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
const int inf = 1 << 28;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 8;
char maz[N][N << 1];
int dp[1 << 8][N][N];
int pl, pw;
int gx, gy;
int H[N][N], cost[N][N];
bool visit[N][N];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
queue<pii> que;

bool check(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

void update(int &value, int w, int x, int y) {
    if (value > w) {
        value = w;
        if (!visit[x][y]) {
            visit[x][y] = true;
            que.push(mp(x, y));
        }
    }
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &pl, &pw);
        memset(H, 0, sizeof(H));
        memset(cost, 0, sizeof(cost));
        int num = 0;
        for (int i = 0; i < N; i++) {
            scanf("%s", maz[i]);
            for (int j = 0; j < N; j++) {
                if (maz[i][j] == '.') {
                    cost[i][j] = pl;
                } else if (maz[i][j] == 'W') {
                    cost[i][j] = pw;
                } else if (maz[i][j] == 'G') {
                    gx = i, gy = j;
                } else if (maz[i][j] == 'H') {
                    H[i][j] = 1 << num;
                    num++;
                }
            }
        }
        int all = 1 << num;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int mask = 0; mask < all; mask++) {
                    dp[mask][i][j] = inf;
                }
                if (H[i][j]) dp[H[i][j]][i][j] = 0;
            }
        }
        for (int mask = 1; mask < all; mask++) {
            memset(visit, false, sizeof(visit));
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (dp[mask][i][j] < inf) {
                        que.push(mp(i, j));
                        visit[i][j] = true;
                    }
                }
            }
            while (!que.empty()) {
                pii now = que.front();
                que.pop();
                visit[now.fi][now.se] = false;
                int tmp = dp[mask][now.fi][now.se];
                for (int i = 0; i < 4; i++) {
                    int nx = now.fi + dx[i];
                    int ny = now.se + dy[i];
                    if (!check(nx, ny)) continue;
                    if (maz[nx][ny] == 'H') {
                        dp[mask | H[nx][ny]][nx][ny] = min(dp[mask | H[nx][ny]][nx][ny], tmp + 1);
                    } else {
                        update(dp[mask][nx][ny], tmp + cost[nx][ny] + 1, nx, ny);
                    }
                }
            }
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    int s = all - 1 - mask;
                    for (int t = s; t; t = (t - 1) & s) {
                        int newMask = t | mask;
                        if (maz[i][j] == 'H') {
                            dp[newMask][i][j] = min(dp[newMask][i][j], dp[mask][i][j] + dp[t | H[i][j]][i][j]);
                        } else {
                            dp[newMask][i][j] = min(dp[newMask][i][j], dp[mask][i][j] + dp[t][i][j] - cost[i][j]);
                        }
                    }
                }
            }
        }
        printf("Case %d: %d\n", Case++, dp[all - 1][gx][gy]);
    }
    return 0;
}
