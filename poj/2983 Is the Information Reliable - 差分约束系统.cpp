#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define maxn 1005
#define maxm 300000
const int inf = 1 << 30;
int n, m, s;
int dist[maxn], cnt[maxn], eh[maxn], tot;
char ch;
bool visit[maxn];

struct Edge {
	int u, v, w, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int w) {
	Edge e = {u, v, w, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void spfa(int s, int n) {
	memset(visit, false, sizeof(visit));
	memset(cnt, 0, sizeof(cnt));
	fill(&dist[0], &dist[maxn], inf);
	dist[s] = 0, visit[s] = true; cnt[s]++;
	queue<int> que;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, w = et[i].w;
			if(dist[v] > w + dist[u]) {
				dist[v] = w + dist[u];
				if(!visit[v]) {
					visit[v] = true;
					que.push(v);
					cnt[v]++;
					if(cnt[v] >= n) {
						printf("Unreliable\n");
						return;
					}
				}
			}
		}
	}
	printf("Reliable\n");
}
	
int main() {
	int u, v, x;
	while(scanf("%d%d\n", &n, &m) != EOF) {
		init();
		for(int i = 0; i < m; i++) {
			scanf("%c", &ch);
			if(ch == 'P') {
				scanf("%d%d%d", &u, &v, &x);
				addedge(u, v, -x);
				addedge(v, u, x);
			}
			else {
				scanf("%d%d", &u, &v);
				addedge(u, v, -1);
			}
			getchar();
		}
		s = 0; //³¬¼¶Ô´µã
		for(int i = 1; i <= n; i++) addedge(s, i, 0);
		spfa(s, n + 1);
	}
	return 0;
}