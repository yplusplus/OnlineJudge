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
const int M = 22222;
vector<pii> dag[N], vec[N];
int n, m, w;
int dfn[N], low[N], cnt[N], s[N], top;
int Dindex, scc, belong[N];
bool instack[N];

void tarjan_dfs(int u) {
    int v;
    dfn[u] = low[u] = ++Dindex;
    s[++top] = u;
    instack[u] = true;
    for(int i = 0; i < vec[i].size(); i++) {
        v = vec[u][i].fi;
        if(!dfn[v]) tarjan_dfs(v), low[u] = min(low[u], low[v]);
        else if(instack[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        scc++;
        do {
            v = s[top--];
            instack[v] = false;
            belong[v] = scc;
            cnt[scc]++;
        } while(u != v);
    }
}

void tarjan() {
    top = scc = Dindex = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(instack, false, sizeof(instack));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) tarjan_dfs(i);
    for(int u = 1; u <= n; u++) {
        for(int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i].fi;
            if(belong[u] == belong[v]) continue;
            dag[belong[u]].pb(mp(belong[v], vec[u][i].se));
        }
    }
}

bool canReach[N][N], visit[N];
void dfs(int u, int s) {
    visit[u] = true;
    canReach[s][u] = true;
    bool flag = false;
    for(int i = 0; i < dag[u].size(); i++) {
        int v = dag[u][i].fi;
        if(!visit[v]) dfs(v, s);
    }
}

void work() {
    tarjan();
    w = 1;
    int ansEdge[M], tot = 0;
    memset(canReach, false, sizeof(canReach));
    for(int i = 1; i <= scc; i++) {
        memset(visit, false, sizeof(visit));
        dfs(i, i);
    }
    for(int u = 1; u <= scc; u++) {
        for(int i = 0; i < dag[u].size(); i++) {
            int v = dag[u][i].fi, id = dag[u][i].se;
            int sum = cnt[u] + cnt[v];
            for(int k = 1; k <= scc; k++) {
                if(k == u || k == v) continue;
                if(canReach[u][k] && canReach[k][v]) sum += cnt[k];
            }
            if(sum > w) {
                w = sum;
                tot = 0;
                ansEdge[tot++] = id;
            } else if(sum == w) {
                ansEdge[tot++] = id;
            }
        }
    }
    sort(ansEdge, ansEdge + tot);
    printf("%d\n", w);
    printf("%d\n", tot);
    for(int i = 0; i < tot; i++) {
        printf("%d%c", ansEdge[i], i == tot - 1 ? '\n' : ' ');
    }
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 1; i <= n; i++) {
            vec[i].clear();
            dag[i].clear();
        }
        for(int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            vec[u].pb(mp(v, i));
        }
        work();
    }
    return 0;
}
