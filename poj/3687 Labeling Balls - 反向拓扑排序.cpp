#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

const int N = 222;
vector<int> vec[N];
int ind[N];
int w[N];
int n, m;

bool solve() {
    priority_queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (ind[i] == 0) {
            que.push(i);
        }
    }
    int alloc = n;
    while (!que.empty()) {
        int u = que.top(); que.pop();
        w[u] = alloc--;
        for (int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i];
            if (--ind[v] == 0) {
                que.push(v);
            }
        }
    }
    return alloc == 0;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) vec[i].clear();
        memset(ind, 0, sizeof(ind));
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            vec[b].push_back(a);
            ind[a]++;
        }
        if (solve()) {
            for (int i = 1; i <= n; i++) {
                printf("%d%c", w[i], i == n ? '\n' : ' ');
            }
        } else cout << -1 << endl;
    }
    return 0;
}
