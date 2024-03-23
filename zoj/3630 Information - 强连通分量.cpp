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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 110
#define maxm 10010
int n, m;
struct edge {
	int v, next;
}et[maxm];
bool visit[maxn];
int dfn[maxn], low[maxn], Dindex, instack[maxn], belong[maxn], scc;
int cnt[maxn];
int s[maxn], top;
int eh[maxn], tot;
void addedge(int u, int v) {
	edge E = {v, eh[u]};
	et[tot] = E;
	eh[u] = tot++;
}
void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}
void dfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u, instack[u] = true;
	for(int i = eh[u]; i != -1; i = et[i].next) {
		v = et[i].v;
        if(visit[v]) continue;
		if(!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
		else if(instack[v]) low[u] = min(low[u], dfn[v]);	
     }
	if(dfn[u] == low[u]) {
		scc++;
		do {
			v = s[top--];
			instack[v] = false;
			belong[v] = scc;
            cnt[scc]++;
		}while(v != u);
	}
}
void tarjan() {
	top = scc = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, 0, sizeof(instack));
	for (int i = 0; i < n; i++)
		if(!dfn[i]) dfs(i);
}

void solve() {
    int ans = inf;
    memset(visit, false, sizeof(visit));
    for(int i = 0; i < n; i++) {
        visit[i] = true;
        memset(cnt, 0, sizeof(cnt));
        tarjan();
        int res = 0;
        for(int j = 1; j <= scc; j++) {
            res = max(res, cnt[j]);
        }
        if(res == 1) res = 0;
        ans = min(ans, res);
        visit[i] = false;
    }
    cout << ans << endl;
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        init();
        int u, v;
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            addedge(u, v);
        }
        solve();
    }
    return 0;
}
