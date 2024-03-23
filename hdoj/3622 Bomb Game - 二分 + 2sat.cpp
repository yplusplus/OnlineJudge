#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
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
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define eps 1e-6
#define maxn 550
int n, nn;
int eh[maxn], tot;
vector<int> vec[maxn];
pdd p[maxn];

int dfn[maxn], low[maxn], Dindex, instack[maxn], belong[maxn], scc;
int s[maxn], top;

double getdist(const pdd &a, const pdd &b) {
    return sqrt((a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se));
}

void dfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u, instack[u] = true;
    int size = vec[u].size();
    for(int i = 0; i < size; i++) {
        v = vec[u][i];
		if(!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
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
	for (int i = 0; i < (nn << 1); i++)
		if(!dfn[i]) dfs(i);
}

bool isOK() {
    for(int i = 0; i < nn; i++)
        if(belong[i] == belong[i+nn]) return false;
    return true;
}

void build(double limit) {
    for(int i = 0; i < (nn << 1); i++) vec[i].clear();
    for(int i = 0; i < n; i++) {
        int a = i << 1, b = i << 1 | 1;
        vec[a].pb(b + nn), vec[b].pb(a + nn);
        vec[a+nn].pb(b), vec[b+nn].pb(a);
        for(int j = 0; j < i; j++) {
            int c = j << 1, d = j << 1 | 1;
            if(getdist(p[a], p[c]) + eps < limit) {
                vec[a].pb(c+nn), vec[a].pb(d);
                vec[c].pb(a+nn), vec[c].pb(b);
            }
            if(getdist(p[a], p[d]) + eps < limit) {
                vec[a].pb(d+nn), vec[a].pb(c);
                vec[d].pb(a+nn), vec[d].pb(b);
            }
            if(getdist(p[b], p[c]) + eps < limit) {
                vec[b].pb(c+nn), vec[b].pb(d);
                vec[c].pb(b+nn), vec[c].pb(a);
            }
            if(getdist(p[b], p[d]) + eps < limit) {
                vec[b].pb(d+nn), vec[b].pb(c);
                vec[d].pb(b+nn), vec[d].pb(a);
            }
        }
    }
}

bool check(double limit) {
    build(limit);
    tarjan();
    return isOK();
}

void solve() {
    double l = 0.0, r = 1e6;
    double ans;
    while(l + eps < r) {
        double mid = (l + r) / 2.0;
        if(check(mid * 2)) ans = mid, l = mid;
        else r = mid;
    }
    printf("%.2f\n", ans);
}

int main() {
    while(~scanf("%d", &n)) {
        nn = n << 1;
        for(int i = 0; i < nn; i++) scanf("%lf%lf", &p[i].fi, &p[i].se);
        solve();
    }
    return 0;
}
