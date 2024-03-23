#include <iostream>
#include <cassert>
#include <queue>
#include <climits>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;
const int N = 33333;
int n, m, K;
vector<PII> vec[N];
vector<PII> tree[N];
int dist[N];
bool visit[N];

void spfa(int s) {
    for (int i = 1; i <= n; i++) dist[i] = INT_MAX, visit[i] = false;
    queue<int> que;
    que.push(s);
    dist[s] = 0;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        visit[u] = false;
        for (int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i].first, w = vec[u][i].second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
}

void sptree(int u) {
    visit[u] = true;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].first, w = vec[u][i].second;
        if (!visit[v] && dist[u] + w == dist[v]) {
            tree[u].push_back(make_pair(v, w));
            tree[v].push_back(make_pair(u, w));
            sptree(v);
        }
    }
}


int son[N], subtree[N];
int que[N], tot;
int dfs(int u, int fa) {
    que[tot++] = u;
    son[u] = 1;
    subtree[u] = 0;
    for (int i = 0; i < tree[u].size(); i++) {
        int v = tree[u][i].first;
        if (!visit[v] && v != fa) {
            dfs(v, u);
            son[u] += son[v];
            subtree[u] = max(subtree[u], son[v]);
        }
    }
}

int find_root(int u) {
    tot = 0;
    dfs(u, 0);
    int cnt = son[u];
    int root = -1;
    for (int i = 0; i < tot; i++) {
        int u = que[i];
        subtree[u] = max(subtree[u], cnt - son[u]);
        if (root == -1 || subtree[u] < subtree[root]) {
            root = u;
        }
    }
    assert(root != -1);
    return root;
}

int longest[N], longest_cnt[N];
int tmp_longest[N], tmp_longest_cnt[N];
int ans_longest, ans_longest_cnt;

void dfs2(int u, int fa, int dep, int length) {
    if (dep > K) return;
    int d = K - dep;
    if (longest_cnt[d] > 0 && length + longest[d] >= ans_longest) {
        if (length + longest[d] > ans_longest) ans_longest_cnt = 0;
        ans_longest = longest[d] + length;
        ans_longest_cnt += longest_cnt[d];
    }

    if (length > tmp_longest[dep]) tmp_longest[dep] = length, tmp_longest_cnt[dep] = 1;
    else if (length == tmp_longest[dep]) tmp_longest_cnt[dep] ++;

    for (int i = 0; i < tree[u].size(); i++) {
        int v = tree[u][i].first, w = tree[u][i].second;
        if (visit[v] || v == fa) continue;
        dfs2(v, u, dep + 1, length + w);
    }
}

void divide(int u) {
    int root = find_root(u);
    int n = son[u];
    if (n <= K) return;
    longest[0] = 0;
    longest_cnt[0] = 1;
    for (int i = 0; i < tree[root].size(); i++) {
        int v = tree[root][i].first, w = tree[root][i].second;
        if (visit[v]) continue;
        dfs2(v, root, 1, w);
        for (int i = 1; i <= n; i++) {
            if (tmp_longest_cnt[i] == 0) break;
            if (tmp_longest[i] > longest[i])
                longest[i] = tmp_longest[i], longest_cnt[i] = tmp_longest_cnt[i];
            else if (tmp_longest[i] == longest[i]) 
                longest_cnt[i] += tmp_longest_cnt[i];
            tmp_longest_cnt[i] = tmp_longest[i] = 0;
        }
    }

    for (int i = 0; i <= n; i++) longest[i] = longest_cnt[i] = 0;

    visit[root] = true;
    for (int i = 0; i < tree[root].size(); i++) {
        int v = tree[root][i].first;
        if (!visit[v]) {
            divide(v);
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) sort(vec[i].begin(), vec[i].end());
    spfa(1);
    for (int i = 1; i <= n; i++) {
        tree[i].clear();
        visit[i] = false;
    }
    sptree(1);
    memset(visit, false, sizeof(visit));
    ans_longest = ans_longest_cnt = 0;
    divide(1);
    printf("%d %d\n", ans_longest, ans_longest_cnt);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &K);
        K--;
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            vec[a].push_back(make_pair(b, c));
            vec[b].push_back(make_pair(a, c));
        }
        solve();
    }
    return 0;
}
