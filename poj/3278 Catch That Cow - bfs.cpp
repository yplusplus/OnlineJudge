#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define maxn 100005
bool visit[maxn];
int ti[maxn];
int n, k;

int cal(int n, int i) {
	if(i == 0) return n - 1;
	if(i == 1) return n + 1;
	if(i == 2) return 2 * n;
}

void bfs() {
	queue<int> que;
	que.push(n);
	ti[n] = 0;
	visit[n] = true;
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		if(u == k) return;
		for(int i = 0; i < 3; i++) {
			int v = cal(u, i);
			if(v >= 0 && v <= 100000 && !visit[v]) {
				que.push(v);
				visit[v] = true;
				ti[v] = ti[u] + 1;
			}
		}
	}
}

int main() {
	cin >> n >> k;
//	memset(visit, false, sizeof(visit));
	bfs();
	cout << ti[k] << endl;
	return 0;
}