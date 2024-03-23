#include "iostream"
#include "cstdio"
#include "queue"
using namespace std;
#define maxn 205
const int INF = 2000000000;
int n, m;
int a[maxn], p[maxn], cap[maxn][maxn];
int maxflow;

int min(int a,int b)
{
	return a < b ? a : b;
}

int ek(int s, int t) {
	maxflow = 0;
	while(1) {
		queue<int> que;
		memset(a, 0, sizeof(a));
		a[s] = INF;
		int flag = 1;
		que.push(s);
		while(!que.empty() && flag) {
			int u = que.front();
			que.pop();
			for(int v = 1; v <= n; v++)
				if(!a[v] && cap[u][v]) {
					p[v] = u;
					a[v] = min(a[u], cap[u][v]);
					if(v == t) {flag = 0; break;}
					que.push(v);
				}
		}
		if(!a[t]) break;
		for(int u = t; u != s; u = p[u]) {
			cap[p[u]][u] -= a[t];
			cap[u][p[u]] += a[t];
		}
		maxflow += a[t];
	}
	return maxflow;
}



int main() {
	while(cin >> m >> n) {
		memset(cap, 0, sizeof(cap));
		for(int i = 0; i < m; i++) {
			int u, v, w;
			cin >> u >> v >>w;
			cap[u][v] += w;
		}
		cout << ek(1, n) << endl;
	}
	return 0;
	
}