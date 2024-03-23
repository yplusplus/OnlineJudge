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
#define maxn 1010
#define maxm 1000050
int dfn[maxn], low[maxn], Dindex, instack[maxn], belong[maxn], scc;
int s[maxn], top;
bool maz[maxn][maxn];
int n, m;
int in[maxn], out[maxn];
int tot;
struct Edge {
    int v, next;
}et[maxm];

void init() {
    tot = 0;
    memset(in, -1, sizeof(in));
    memset(out, -1, sizeof(out));
}

void addedge(int u, int v, int head[]) {
    Edge e = {v, head[u]};
    et[tot] = e;
    head[u] = tot++;
}

void tarjan_dfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u, instack[u] = true;
    for(int v = 1; v <= n; v++) {
        if(!maz[u][v]) continue;
		if(!dfn[v]) tarjan_dfs(v), low[u] = min(low[u], low[v]);
		else if(instack[v]) low[u] = min(low[u], dfn[v]);	
     }
	if(dfn[u] == low[u]) {
		scc++;
		do {
			v = s[top--];
			instack[v] = false;
			belong[v] = scc;
		}while(v != u);
	}
}

void tarjan() {
	top = scc = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, 0, sizeof(instack));
	for (int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan_dfs(i);

    tot = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(maz[i][j] && belong[i] != belong[j]) {
                addedge(belong[i], belong[j], out);
                addedge(belong[j], belong[i], in);
            }
        }
    }
    for(int k = 1; k <= scc; k++) {
        for(int i = in[k]; i != -1; i = et[i].next)
            for(int j = out[k]; j != -1; j = et[j].next) {
                int ii = et[i].v, jj = et[j].v;
                if(!maz[ii][jj]) {
                    maz[ii][jj] = 1;
                    addedge(jj, ii, in);
                    addedge(ii, jj, out);
                }
            }
    }
}
int Mx[maxn], My[maxn];
int dx[maxn], dy[maxn], dis;
bool vist[maxn];
bool searchP() {
    queue<int> Q;
    dis = inf;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for (int i = 1; i <= scc; ++i) {
        if (Mx[i] == -1) {
            Q.push(i); dx[i] = 0;
        }
    }
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        if (dx[u] > dis) break;
        for (int i = out[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            if (dy[v] == -1) {
                dy[v] = dx[u] + 1;
                if (My[v] == -1) dis = dy[v];
                else {
                    dx[My[v]] = dy[v] + 1;
                    Q.push(My[v]);
                }
            }
        }
    }
    return dis != inf;
}

bool dfs(int u) {
    for (int i = out[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (!vist[v] && dy[v] == dx[u] + 1) {
            vist[v] = true;
            if (My[v] != -1 && dy[v] == dis) continue;
            if (My[v] == -1 || dfs(My[v])) {
                My[v] = u, Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}

int Match() {
    memset(Mx, -1, sizeof(Mx));
    memset(My, -1, sizeof(My));
    int cnt = 0;
    while(searchP()) {
        memset(vist, false, sizeof(vist));
        for(int i = 1; i <= scc; i++)
            if(Mx[i] == -1 && dfs(i)) cnt++;
    }
    return cnt;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        memset(maz, false, sizeof(maz));
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            maz[u][v] = 1;
        }
        tarjan();
        printf("Case %d: %d\n", Case++, scc - Match());
    }
    return 0;
}
