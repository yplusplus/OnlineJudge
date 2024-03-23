#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 888;
int n;

struct UFS {
    int fa[N];
    void init() { for (int i = 0; i < N; i++) fa[i] = i; }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    bool Union(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        fa[a] = b;
        return true;
    }
} ufs;

int main() {
    while (~scanf("%d", &n)) {
        vector<pair<int, pair<int, int> > > vec;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x;
                scanf("%d", &x);
                if (i > j)
                    vec.push_back(make_pair(x, make_pair(i, j)));
            }
        }
        ufs.init();
        sort(vec.begin(), vec.end());
        int ans = vec.begin()->first;
        int cc = n;
        for (int i = 0; i < vec.size() && cc > 1; i++) {
            ans = vec[i].first;
            int j = i;
            while (j + 1 < vec.size() && vec[j + 1].first == vec[i].first) j++;
            for (int k = i; k <= j; k++) {
                cc -= ufs.Union(vec[k].second.first, vec[k].second.second);
            }
            i = j;
        }
        cout << ans << endl;
    }
    return 0;
}
