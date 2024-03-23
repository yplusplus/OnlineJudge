#include <iostream>
#include <algorithm>
#include <functional>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

const int N = 111;
vector<int> vec[N];
char board[N][N];
bool visit[N];
int match[N];
int color[N][N];
int row[N], col[N];
int cnt[N][N];
int n;

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
    memset(match, -1, sizeof(match));
    int res = 0;
    for (int i = 0; i < n; i++) {
        memset(visit, false, sizeof(visit));
        res += dfs(i);
    }
    return res;
}

void build() {
    for (int i = 0; i < n; i++) { vec[i].clear(); }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (cnt[i][j]) vec[i].push_back(j);
        }
    }
}

void solve() {
    int ans = 0;
    memset(color, 0, sizeof(color));
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == '*') {
                cnt[i][j]++;
                row[i]++, col[j]++;
            }
        }
    }
    ans = max(*max_element(row, row + n), *max_element(col, col + n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            while (row[i] < ans && col[j] < ans) {
                row[i]++;
                col[j]++;
                cnt[i][j]++;
            }
        }
    }
    ans = 0;
    while (true) {
        build();
        int ret = Match();
        if (ret == 0) break;
        ans++;
        for (int i = 0; i < n; i++) {
            if (match[i] != -1) {
                cnt[match[i]][i]--;
                if (board[match[i]][i] == '*') color[match[i]][i] = ans;
            }
        }
    }
    assert(ans == max(*max_element(row, row + n), *max_element(col, col + n)));
    printf("%d\n", ans);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%c", color[i][j], j == n - 1 ? '\n' : ' ');
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", board[i]);
        }
        solve();
    }
    return 0;
}
