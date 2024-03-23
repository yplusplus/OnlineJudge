#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int inf = 1 << 30;
const int N = 555;
int weight[N][N];
int dist[N];
bool visit[N];
int sp;
int s[N];
int pre[N];
int edge[N][N];
int n, m;

void solve() {
    memset(edge, -1, sizeof(edge));
    for (int i = 1; i <= n; i++) {
        dist[i] = inf;
        visit[i] = false;
        pre[i] = -1;
    }
    sp = 0;
    dist[1] = 0;
    int mst = 0;
    while (true) {
        int u = -1;
        for (int i = 1; i <= n; i++) {
            if (!visit[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        if (u == -1) break;
        //cout << u << endl;
        for (int i = 0; i < sp; i++) {
            edge[u][s[i]] = max(weight[u][pre[u]], edge[pre[u]][s[i]]);
            edge[s[i]][u] = edge[u][s[i]];
        }
        s[sp++] = u;
        mst += dist[u];
        //cout << u << " " << dist[u] << endl;
        visit[u] = true;
        for (int i = 1; i <= n; i++) {
            if (!visit[i] && weight[i][u] != -1) {
                if (dist[i] > weight[i][u]) {
                    dist[i] = weight[i][u];
                    pre[i] = u;
                }
            }
        }
    }
    cout << "Cost: " << mst << endl;
    int ans = inf;
    if (m == n - 1) {
        cout << "Cost: " << -1 << endl;
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (weight[i][j] != -1) {
                    if (pre[i] == j || pre[j] == i) {
                    } else {
                        ans = min(ans, mst + weight[i][j] - edge[i][j]);
                    }
                }
            }
        }
        cout << "Cost: " << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    memset(weight, -1, sizeof(weight));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        weight[a][b] = weight[b][a] = c;
    }

    solve();

    return 0;
}
