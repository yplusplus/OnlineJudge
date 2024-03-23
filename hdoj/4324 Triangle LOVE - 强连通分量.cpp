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
#define maxn 2010
int dfn[maxn], low[maxn], Dindex, instack[maxn], belong[maxn], scc;
int s[maxn], top;
char maz[maxn][maxn];
int n, m;
void dfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u, instack[u] = true;
    for(int v = 0; v < n; v++) {
       if(maz[u][v] == '0') continue; 
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
bool tarjan() {
	top = scc = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(instack, 0, sizeof(instack));
	for (int i = 0; i < n; i++)
		if(!dfn[i]) dfs(i);
    if(scc < n) return true;
    return false;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%s", maz[i]);
        printf("Case #%d: ", Case++);
        if(tarjan()) puts("Yes");
        else puts("No");
    }
    return 0;
}
