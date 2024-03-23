#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;

const int N = 111111;

int n, m;
map<int, int> edge[N];
int deg[N];
int in_sum[N];
int value[N];
vector<pair<int, int> > out[N];

void solve() {
    for (int i = 1; i <= n; i++) {
        in_sum[i] = 0;
        value[i] = 0;
        out[i].clear();
    }
    for (int i = 1; i <= n; i++) {
        for (map<int, int>::iterator it = edge[i].begin(); it != edge[i].end(); ++it) {
            if (deg[i] < deg[it->first] || (deg[i] == deg[it->first] && i < it->first)) {
                out[i].push_back(*it);
            }
        }
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int cmd, u, x;
        scanf("%d", &cmd);
        switch (cmd) {
            case 0:
                scanf("%d%d", &u, &x);
                value[u] += x;
                for (int i = 0; i < out[u].size(); i++) {
                    int v = out[u][i].first;
                    in_sum[v] += x * out[u][i].second;
                }
                break;
            case 1:
                scanf("%d", &u);
                int ans = in_sum[u];
                for (int i = 0; i < out[u].size(); i++) {
                    ans += value[out[u][i].first] * out[u][i].second;
                }
                printf("%d\n", ans);
                break;
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
            deg[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            if (!edge[u].count(v)) {
                deg[u]++; deg[v]++;
            }
            edge[u][v]++; edge[v][u]++;
        }
        solve();
    }
    return 0;
}
