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

const int N = 1111;
vector<int> vec[N];
int n, root;
int fa[N];
bool used[N];
void dfs(int u) {
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa[u]) { continue; }
        fa[v] = u;
        dfs(v);
    }
}

struct Node {
    int cnt, sum, cost;
    Node(int _cnt, int _sum, int _cost) : cnt(_cnt), sum(_sum), cost(_cost) {}
    Node() {}
} node[N];

bool cmp(const Node &a, const Node &b) {
    return a.cnt * b.sum < b.cnt * a.sum;
}

void ChangeFather(int father, int child) {
    for (int i = 1; i <= n; i++) {
        if (!used[i] && fa[i] == child) fa[i] = father;
    }
}

int main() {
    while (~scanf("%d%d", &n, &root), n + root) {
        for (int i = 1; i <= n; i++) {
            int value;
            scanf("%d", &value);
            node[i] = Node(1, value, 0);
            vec[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            vec[b].pb(a);
        }
        memset(fa, 0, sizeof(fa));
        dfs(root);
        memset(used, false, sizeof(used));
        int cnt = 1, ans = 0;
        for (int i = 1; i <= n; i++) {
            int idx = -1;
            for (int j = 1; j <= n; j++) {
                if (used[j]) continue;
                if (idx == -1 || cmp(node[j], node[idx])) idx = j;
            }
            int t = fa[idx];
            used[idx] = true;
            ChangeFather(t, idx);
            if (t) {
                node[t] = Node(node[t].cnt + node[idx].cnt, node[t].sum + node[idx].sum, node[idx].sum * node[t].cnt + node[idx].cost + node[t].cost);
            } else {
                ans += cnt * node[idx].sum + node[idx].cost;
                cnt += node[idx].cnt;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
