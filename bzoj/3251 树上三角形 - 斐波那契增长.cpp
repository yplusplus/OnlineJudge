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

const int N = 111111;
int fa[N], v[N], dep[N];
int n;
vector<int> vec[N];

void bfs(int s) {
    queue<int> que;
    que.push(s);
    dep[s] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = 0; i < vec[u].size(); i++) {
            dep[vec[u][i]] = dep[u] + 1;
            que.push(vec[u][i]);
        }
    }
}

int que[111], tot;
bool check(int a, int b) {
    tot = 0;
    if (dep[a] < dep[b]) swap(a, b);
    while (dep[a] > dep[b] && tot <= 50) {
        que[tot++] = v[a];
        a = fa[a];
    }
    while (a != b && tot <= 50) {
        que[tot++] = v[a];
        que[tot++] = v[b];
        a = fa[a], b = fa[b];
    }
    que[tot++] = v[a];
    if (tot > 50) return true;
    if (tot < 3) return false;
    sort(que, que + tot);
    for (int i = 0; i + 2 < tot; i++) {
        if (que[i] > que[i + 2] - que[i + 1]) return true;
    }
    return false;
}

int main() {
    int a, b, q, cmd;
    while (~scanf("%d%d", &n, &q)) {
        for (int i = 1; i <= n; i++) scanf("%d", &v[i]), vec[i].clear();
        for (int i = 1; i < n; i++) {
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            fa[b] = a;
        }
        bfs(1);
        while (q--) {
            scanf("%d%d%d", &cmd, &a, &b);
            //cin >> cmd >> a >> b;
            if (cmd) {
                v[a] = b;
            } else {
                puts(check(a, b) ? "Y" : "N");
            }
        }
    }
    return 0;
}
