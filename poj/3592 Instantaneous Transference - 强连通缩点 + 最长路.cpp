#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
#include "queue"
using namespace std;
#define maxn 1605
const int inf = 1 << 30;
struct Edge {
	int v, w;
};
int n, m;
char maz[50][50];
int dfn[maxn], low[maxn], Dindex, scc, belong[maxn], dist[maxn], score[maxn], w[maxn];;
int magic[maxn], cnt;
int s[maxn], top;
bool instack[maxn], visit[maxn];
vector<int> vec[maxn];
vector<Edge> dag[maxn];

void dfs(int u) {
    int v;
    dfn[u] = low[u] = ++Dindex;
    s[++top] = u;
    instack[u] = true;
    int size = vec[u].size();
    for(int i = 0; i < size; i++) {
        v = vec[u][i];
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[v], low[u]);
        } else if(instack[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        w[++scc] = 0;
        do {
			v = s[top--];
			instack[v] = false;
            belong[v] = scc;   
			w[scc] += score[v];
        }while(v != u);
    }
}

void tarjan() {
	top = scc = Dindex = 0;
	memset(instack, false, sizeof(instack));
	memset(dfn, 0, sizeof(dfn));
	for(int i = 0; i < n * m; i++)
		if(!dfn[i]) dfs(i);
	for(int u = 0; u < n * m; u++) {
		int size = vec[u].size();
		for(int i = 0; i < size; i++) {
			int v = vec[u][i];
			if(belong[u] != belong[v]) {
				Edge e = {belong[v], w[belong[v]]};
				dag[belong[u]].push_back(e);
			}
		}
	}
	Edge e = {belong[0], w[belong[0]]};
	dag[0].push_back(e);
}

int spfa(int s) {
	fill(&dist[0], &dist[maxn], -inf);
	memset(visit, false, sizeof(visit));
	dist[s] = 0, visit[s] = true;
	queue<int> que;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		int size = dag[u].size();
		for(int i = 0; i < size; i++) {
			int v = dag[u][i].v, w = dag[u][i].w;
			if(dist[v] < dist[u] + w) {
				dist[v] = dist[u] + w;
				if(!visit[v]) {
					que.push(v);
					visit[v] = false;
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= scc; i++)
		ans = max(ans, dist[i]);
	return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        getchar();
        cnt = 0;
		for(int i = 0; i < maxn; i++) vec[i].clear(), dag[i].clear();
        for(int i = 0; i < n; i++) scanf("%s", maz[i]);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				int u = i * m + j;
				if(maz[i][j] == '#') score[u] = -1;
				else {
					if(maz[i][j] == '*') {
						magic[cnt++] = u;
						score[u] = 0;
					}
					else score[u] = maz[i][j] - '0';
					if(j + 1 < m && maz[i][j+1] != '#') vec[u].push_back(u + 1);
					if(i + 1 < n && maz[i+1][j] != '#') vec[u].push_back(u + m);
				}
			}
		}
        for(int i = 0; i < cnt; i++) {
            int ii, jj, v;
            scanf("%d%d", &ii, &jj);
			v = ii * m + jj;
			if(score[v] == -1) continue;
            vec[magic[i]].push_back(v);
        }
        tarjan();	//Ëõµã¹¹ÐÂÍ¼ - dag
        cout << spfa(0) << endl;
    }
    return 0;
}