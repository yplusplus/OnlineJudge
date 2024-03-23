#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

typedef pair<int, int> Monster;
const int N = 111;
vector<int> vec[N];
int match[N];
bool visit[N];
Monster A[N], B[N];
int n;

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
        memset(visit, false, sizeof(visit));
        res += dfs(i);
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &A[i].first, &A[i].second);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &B[i].first, &B[i].second);
        }
        for (int i = 0; i < n; i++) vec[i].clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i].first > B[j].second && A[i].second >= B[j].first) {
                    vec[i].push_back(j);
                }
            }
        }
        int ret = Match();
        puts(ret == n ? "Yes" : "No");
    }
    return 0;
}
