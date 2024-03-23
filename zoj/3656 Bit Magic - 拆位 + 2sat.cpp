#include "iostream"
#include "cstdio"
#include "vector"
#include "cstring"
using namespace std;
#define pb push_back
const int N = 1111;
int n, m;
vector<int> vec[N];
int belong[N], scc, dfn[N], low[N], Dindex;
int s[N], top;
bool instack[N];
int b[N][N];
void dfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u, instack[u] = true;
    for(int i = 0; i < vec[u].size(); i++) {
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
	memset(instack, false, sizeof(instack));
	memset(dfn, 0, sizeof(dfn));
	for(int i = 0; i < (n << 1); i++)
		if(!dfn[i]) dfs(i);
}
bool check(int mask) {
    for(int i = 0; i < (n << 1); i++) vec[i].clear();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) {
                if(b[i][j]) return false;
            } else if(i % 2 == 1 && j % 2 == 1) {
                if(b[i][j] & mask) vec[i].pb(j+n), vec[j].pb(i+n);
                else vec[i+n].pb(i), vec[j+n].pb(j);
            } else if(i % 2 == 0 && j % 2 == 0) {
                if(b[i][j] & mask) vec[i].pb(i+n), vec[j].pb(j+n);
                else vec[i+n].pb(j), vec[j+n].pb(i);
            } else {
                if(b[i][j] & mask) vec[i].pb(j+n), vec[j].pb(i+n), vec[i+n].pb(j), vec[j+n].pb(i);
                else vec[i].pb(j), vec[j].pb(i), vec[i+n].pb(j+n), vec[j+n].pb(i+n);
            }
        }
    }
    tarjan();
	for(int i = 0; i < n; i++)
		if(belong[i] == belong[i+n]) return false;
	return true;
}

int main() {
	while(~scanf("%d", &n)) {
        bool found = false;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &b[i][j]);
        for(int i = 0; i < 32; i++) {
            if(!check(1LL << i)) {
                found = true;
                break;
            }
        }
        puts(found ? "NO" : "YES");
	}
	return 0;
}
