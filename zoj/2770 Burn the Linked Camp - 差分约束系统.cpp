#include "iostream"
#include "cstdio"
#include "queue"
#include "cstring"
using namespace std;
#define maxn 1005
#define maxm 25000
const int inf = 1 << 30;
int n, m, s;
int eh[maxn], tot, dist[maxn], cap[maxn], cnt[maxn];
bool visit[maxn];

struct Edge {
	int u, v, w, next;
}et[maxm];

void init() {
	tot = 0;
	cap[0] = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int w) {
	Edge e = {u, v, w, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

bool spfa(int s, int n) {
	memset(cnt, 0, sizeof(cnt));
	memset(visit, false, sizeof(visit));
	fill(&dist[0], &dist[maxn], inf);
	dist[s] = 0, visit[s] = true, cnt[s]++;
	queue<int> que;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, w = et[i].w;
			if(dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if(!visit[v]) {
					visit[v] = true;
					que.push(v);
					if(++cnt[v] >= n) return false;
				}
			}
		}
	}
	return true;
}

int main() {
	int u, v, k;
	while(scanf("%d%d", &n, &m) !=	EOF) {
		init();
		for(int i = 1; i <= n; i++) {
			scanf("%d", &cap[i]);
			addedge(i - 1, i, cap[i]);
			addedge(i, i - 1, 0);
			cap[i] += cap[i-1];
		}
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &v, &u, &k);
			addedge(u, v - 1, -k);
			addedge(v - 1, u, cap[u] - cap[v-1]);
		}
		s = n + 1;	//³¬¼¶Ô´µã
		for(int i = 0; i <= n; i++) addedge(s, i, 0);
		if(spfa(s, n + 2)) printf("%d\n", dist[n]- dist[0]);
		else printf("Bad Estimations\n");		
	}
	return 0;
}