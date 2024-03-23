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
const int N = 11111;
const int M = 222222;
int n, m, root;
int eh[N], tot, belong[N], bcc, dfn[N], low[N], Dindex;
int s[N], top;
int visit[N];
int fa[N], cnt[N];
struct Edge {
    int v, next;
}et[M];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
    memset(cnt, 0, sizeof(cnt));
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void Union(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    fa[a] = b;
    cnt[b] += cnt[a];
    return;
}

void addedge(int u, int v) {
    Edge e = {v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void dfs(int u, int pre) {
    dfn[u] = low[u] = ++Dindex , visit[u] = 1 ;
    s[++top] = u;
    int tot = 0;
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if(visit[v] == 1 && v != pre) low[u] = min(low[u], dfn[v]);
        if(visit[v] == 0) {
            dfs(v, u);
            tot++, low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u]) { // 桥
                bcc++; //[0, bcc]
                while(1) {// 缩点 , 也可以直接利用 low[] 来缩点 ,low 属于 [1, n]
                    belong[s[top]] = bcc;
                    if(s[top--] == v) break;
                }
            }
        }
    }
    visit[u] = 2;
}

void tarjan() {
    top = bcc = Dindex = 0;
    memset(visit, 0, sizeof(visit));
    memset(belong, 0, sizeof(belong));
    for(root = 0; root < n; root++) {
        if(!visit[root]) dfs(root, -1);
        if (top) {
            bcc++;
            while (top) belong[s[top--]] = bcc;
        }
    }
}

int __cnt[N];

int __dfs(int u, int fa) {
    visit[u] = true;
    __cnt[u] = 1;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (visit[v] || cnt[belong[v]] > 1) continue;
        __cnt[u] += __dfs(v, u);
    }
    return __cnt[u];
}

int main() {
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        init();
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--, b--;
            addedge(a, b);
            addedge(b, a);
        }
        tarjan();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (belong[i] >= 0) cnt[belong[i]]++;
        }
        memset(visit, 0, sizeof(visit));
        for (int i = 0; i < n; i++) {
            if (!visit[i] && cnt[belong[i]] == 1) {
                int tmp = __dfs(i, -1);
                ans += tmp * (tmp - 1);
            }
        }
        ans >>= 1;
        printf("Case #%d: %d\n", Case++, ans);
    }
    return 0;
}
