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
const int M = 111;
const int N = 3333;
vector<int> vec[N];
char maz[M][M];
int row[M][M], col[M][M];
int cnt_row, cnt_col;
int n, m;

void build() {
    for (int i = 0; i < cnt_row; i++) vec[i].clear();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (maz[i][j] == '*') {
                vec[row[i][j]].pb(col[i][j]);
            }
        }
    }
}

int match[N];
bool visit[N];
bool dfs(int u) {
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) {
            visit[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}
int Match() {
    int cnt = 0;
    memset(match, -1, sizeof(match));
    for (int i = 0; i < cnt_row; i++) {
        memset(visit, false, sizeof(visit));
        if (dfs(i)) cnt++;
    }
    return cnt;
}

int solve() {
    build();
    return Match();
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        memset(maz, '.', sizeof(maz));
        for (int i = 1; i <= n; i++) maz[i][m + 1] = '#';
        for (int j = 1; j <= n; j++) maz[n + 1][j] = '#';
        int cnt, x, y;
        scanf("%d", &cnt);
        while (cnt--) {
            scanf("%d%d", &x, &y);
            maz[x][y] = '*';
        }
        scanf("%d", &cnt);
        while (cnt--) {
            scanf("%d%d", &x, &y);
            maz[x][y] = '#';
        }
        cnt_row = cnt_col = 0;
        for (int i = 1; i <= n; i++) {
            bool flag = false;
            for (int j = 1; j <= m + 1; j++) {
                if (maz[i][j] == '*') row[i][j] = cnt_row, flag = true;
                else if (maz[i][j] == '#') {
                    if (flag) cnt_row++;
                    flag = false;
                }
            }
        }
        for (int j = 1; j <= m; j++) {
            bool flag = false;
            for (int i = 1; i <= n + 1; i++) {
                if (maz[i][j] == '*') col[i][j] = cnt_col, flag = true;
                else if (maz[i][j] == '#') {
                    if (flag) cnt_col++;
                    flag = false;
                }
            }
        }
        printf("%d\n", solve());
    }
    return 0;
}
