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
const int N = 222222;
int need[N];
int n;
int eh[N], tot;

//直接在树上贪心
//对于changed的边，尽量离根节点越近越好
//因为这样不会比其他方案更差

struct Edge {
    int v, id, p, next;
}et[N];
int changed[N], ansTot;

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v, int id, int p) {
    Edge e = {v, id, p, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void prepare(int u, int dep, int cnt) {
    need[u] = 0;
    need[u] = max(need[u], (dep + 1) / 2 - cnt);
    for (int i = eh[u]; i != -1; i = et[i].next) {
        prepare(et[i].v, dep + 1, cnt + et[i].p);
        need[u] = max(need[u], need[et[i].v]);
    }
}

void dfs(int u, int cnt) {
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (cnt >= need[v]) continue;
        if (!et[i].p) {
            changed[ansTot++] = et[i].id;
            dfs(v, cnt + 1);
        } else {
            dfs(v, cnt);
        }
    }
}

int main() {
    char str[10], trash[10];
    while (cin >> n) {
        init();
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d%s", &a, &b, str);
            if (str[0] == 'a') {
                scanf("%s", trash);
            }
            addedge(b, a, i, str[0] == 'p');
        }
        ansTot = 0;
        prepare(1, 0, 0);
        dfs(1, 0);
        cout << ansTot << endl;
        for (int i = 0; i < ansTot; i++) {
            printf("%d%c", changed[i], i == ansTot - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
