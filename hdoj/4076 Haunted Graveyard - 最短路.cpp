#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define maxn 1000
#define maxm 50000
const int inf = 1 << 30;
int n, e, g;
int r, c, s, t;
int eh[maxn], tot, dist[maxn], cnt[maxn];
bool visit[maxn];
int maz[35][35];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
struct Edge {
	int u, v, cost, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int cost) {
	Edge e = {u, v, cost, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

bool spfa(int s, int n) {
	queue<int> que;
	fill(&dist[0], &dist[maxn], inf);
	memset(visit, false, sizeof(visit));
	memset(cnt, 0, sizeof(cnt));
	que.push(s);
	dist[s] = 0, visit[s] = true, cnt[s]++;
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, cost = et[i].cost;
			if(dist[v] > dist[u] + cost) {
				dist[v] = dist[u] + cost;
				if(!visit[v] && v != t) {//判负环不能把终点算在内
					que.push(v);
					visit[v] = true;
					if(++cnt[v] >= n) return false;
				}
			}
		}
	}
	return true;
}

bool check(int x, int y) {
	if(x >= 0 && x < r && y >= 0 && y < c) return true;
	return false;
}

int pos(int x, int y) {
	return x * c + y;
}

int main() {
	while(~scanf("%d%d", &r, &c)) {
		if(!r && !c) break;
		init();
		memset(maz, 0, sizeof(maz));
		scanf("%d", &g);
		for(int i = 0; i < g; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			maz[a][b] = -1;
		}
		scanf("%d", &e);
		for(int i = 1; i <= e; i++) {
			int a, b, c, d, e;
			scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
			maz[a][b] = i;
			addedge(pos(a, b), pos(c, d), e);
		}
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				if(maz[i][j] == 0) {
					for(int k = 0; k < 4; k++) {
						int x = i + dx[k], y = j + dy[k];
						if(check(x, y) && maz[x][y] != -1) addedge(pos(i, j), pos(x, y), 1);
					}
				}
			}
		}
		s = 0, t = pos(r - 1, c - 1);
		if(!spfa(s, r * c - g)) printf("Never\n");
		else if(dist[t] == inf) printf("Impossible\n");
		else printf("%d\n", dist[t]);
	}
	return 0;
}