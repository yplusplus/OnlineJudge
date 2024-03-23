#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <map>
using namespace std;
const int N = 11111;
typedef pair<int, int> pii;
int fa[N], space[N];
bool visit[N];
set<pii> s[N];
map<pii, int> mp;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool check(int x, int y) {
	return x > 0 && y > 0;
}

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void Union(int a, int b) {
	a = find(a), b = find(b);
    if (s[a].size() < s[b].size()) swap(a, b);
    for (set<pii>::iterator it = s[b].begin(); it != s[b].end(); it++) {
        s[a].insert(*it);
    }
    fa[b] = a;
    space[a] += space[b];
}

void remove(int a) {
    a = find(a);
    fa[a] = -1;
    for (set<pii>::iterator it = s[a].begin(); it != s[a].end(); it++) {
        mp.erase(*it);
        int x = it->first, y = it->second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (check(nx, ny)) {
                if (mp.count(make_pair(nx, ny)) == 0) continue;
                int id = mp[make_pair(nx, ny)];
                int root = find(id);
                if (root ^ a & 1) space[root]++;
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            s[i].clear();
            space[i] = 0;
        }
        mp.clear();
        for (int i = 1; i <= n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            s[i].insert(make_pair(x, y));
            mp[make_pair(x, y)] = i;
            int cnt = 0;
            vector<int> vec[2];
            int id, root;
            for (int j = 0; j < 4; j++) {
                int nx = x + dx[j], ny = y + dy[j];
                if (check(nx, ny)) {
                    cnt++;
                    if (mp.count(make_pair(nx, ny)) == 0) continue;
                    id = mp[make_pair(nx, ny)];
                    root = find(id);
                    space[root]--;
                    if ((i ^ root) & 1) {
                        vec[1].push_back(root);
                    } else {
                        vec[0].push_back(root);
                        Union(root, i);
                    }
                }
            }
            root = find(i);
            space[root] += cnt - vec[0].size() - vec[1].size();
            bool found = true;
            for (int j = 0; j < vec[1].size(); j++) {
                id = vec[1][j];
                root = find(id);
                if (space[root] == 0) { remove(root); }
            }
            root = find(i);
            if (space[root] == 0) remove(root);
        }
        int nb = 0, nw = 0;
        for (int i = 1; i <= n; i++) {
            if (fa[i] == i) {
                if (i & 1) nb += s[i].size();
                else nw += s[i].size();
            }
        }
        printf("%d %d\n", nb, nw);
    }
}

