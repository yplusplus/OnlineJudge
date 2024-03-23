#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
#include "string"
using namespace std;
int n, m;
bool visit[1<<22];
int edge[22];
string ans;
struct Node {
	int mask;
	string path;
	Node(){}
	Node(int _mask, string _path) {
		mask = _mask, path = _path;
	}
};

bool bfs() {
	queue<Node> que;
	memset(visit, false, sizeof(visit));
	que.push(Node((1 << n) - 1, ""));
	visit[(1<<n)-1] = true;
	while(!que.empty()) {
		Node now = que.front();
		que.pop();
		for(int i = 0; i < n; i++) {
			if(now.mask & (1 << i)) {
				int mask = now.mask ^ (1 << i);
				int newmask = 0;
				for(int j = 0; j < n; j++)
					if(mask & (1 << j)) newmask |= edge[j];
				if(visit[newmask]) continue;
				visit[newmask] = true;
				char ch = i + '0';
				string tmp = now.path + ch;
				if(newmask == 0) {
					ans = tmp;
					return true;
				}
				que.push(Node(newmask, tmp));
			}
		}
	}
	return false;
}

void solve() {
	if((m > n - 1) || !bfs()) printf("Impossible\n");
	else {
		printf("%d:", ans.length());
		for(int i = 0; i < ans.length(); i++) printf(" %d", ans[i] - '0');
		printf("\n");
	}
	return;
}

int main() {
	while(~scanf("%d%d", &n, &m)) {
		if(!n && !m) break;
		memset(edge, 0, sizeof(edge));
		for(int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			edge[u] |= (1 << v), edge[v] |= (1 << u);
		}
		solve();
	}
	return 0;
}