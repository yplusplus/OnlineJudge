#include "iostream"
#include "cstdio"
#include "cstring"
#include "vector"
using namespace std;
#define maxn 10005
int n, m;
bool visit[maxn];
int cnt[maxn], eh[maxn], ans, tot;
struct Edge {
	int v, next;
}et[1000005];
void addedge(int u, int v) {
	Edge e = {v, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}
void init() {
	tot = ans = 0;
	memset(eh, -1, sizeof(eh));
	memset(visit, false, sizeof(visit));
}
int bfs() {
	int size;
	vector<int> vec;
	vec.clear();
	vec.push_back(1);
	while(size = vec.size()) {
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i < size; i++) {
			for(int j = eh[vec[i]]; j != -1; j = et[j].next)
				cnt[et[j].v]++;
		}
		vec.clear();
		for(int i = 2; i <= n; i++) {
			if(!visit[i] && cnt[i] != size) {
				visit[i] = true;
				vec.push_back(i);
				ans++;
			}
		}
	}
	return ans;
}
int main() {
	int T = 1;
	while(~scanf("%d%d", &n, &m)) {
		if(!n && !m) break;
		init();
		for(int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			addedge(u, v), addedge(v, u);
		}
		printf("Case %d: %d\n", T++, bfs());
	}
	return 0;
}