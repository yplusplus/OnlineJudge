#pragma comment(linker,"/STACK:1024000000,1024000000")
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

const int N = 55555;
int pos[N], tot;
int son[N];
int n, m;
vector<int> vec[N];

struct Person {
    int a, b, id;
    void read() {
        scanf("%d%d", &b, &a);
    }
    bool operator<(const Person &x) const {
        if (a != x.a) return a > x.a;
        return pos[id] < pos[x.id];
    }
} person[N];

struct SegmentTree {
    pii node[N << 2];
    void build(int p, int l, int r) {
        node[p] = mp(-1, -1);
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
    void pushup(int p) {
        node[p] = max(node[p << 1], node[p << 1 | 1]);
    }
    void update(int p, int l, int r, int x, pii v) {
        if (l == r) {
            node[p] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) update(p << 1, l, mid, x, v);
        else update(p << 1 | 1, mid + 1, r, x, v);
        pushup(p);
    }
    pii query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return node[p];
        }
        int mid = (l + r) >> 1;
        pii ret = mp(-1, -1);
        if (L <= mid) ret = max(ret, query(p << 1, l, mid, L, R));
        if (R > mid) ret = max(ret, query(p << 1 | 1, mid + 1, r, L, R));
        return ret;
    }
} segmentTree;

void dfs(int u) {
    son[u] = 1;
    pos[u] = tot++;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        dfs(v);
        son[u] += son[v];
    }
}

int ans[N];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) vec[i].clear();
        for (int i = 1; i < n; i++) {
            int father;
            scanf("%d", &father);
            vec[father].pb(i);
            person[i].read();
            person[i].id = i;
        }
        tot = 0;
        dfs(0);
        sort(person + 1, person + n);
        segmentTree.build(1, 1, n - 1);
        for (int i = 1; i < n; i++) {
            int u = person[i].id;
            ans[u] = segmentTree.query(1, 1, n - 1, pos[u], pos[u] + son[u] - 1).se;
            segmentTree.update(1, 1, n - 1, pos[u], mp(person[i].b, u));
        }
        while (m--) {
            int a;
            scanf("%d", &a);
            printf("%d\n", ans[a]);
        }
    }
    return 0;
}
