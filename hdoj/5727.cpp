#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 10;
vector<int> vec[N];
bool mat[N][N];
int a[N];

bool visit[N];
int match[N];
int n, m;

bool dfs(int u) {
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (visit[v]) continue;
        visit[v] = true;
        if (match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int Match() {
    int res = 0;
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; i++) {
        memset(visit, 0, sizeof(visit));
        if (dfs(i)) res++;
    }
    return res;
}

void solve() {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    int ans = 0;
    if (n == 0) {
        puts("0");
        return;
    }
    do {
        for (int i = 0; i < n; i++) {
            vec[i].clear();
            for (int j = 0; j < n; j++) {
                if (mat[i][a[j]] == 0 && mat[i][a[(j + 1) % n]] == 0) {
                    vec[i].push_back(j);
                }
            }
        }
        ans = max(ans, Match());
    } while (next_permutation(a + 1, a + n));
    printf("%d\n", n - ans);
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--, b--;
            mat[a][b] = 1;
        }
        solve();
    }
    return 0;
}
