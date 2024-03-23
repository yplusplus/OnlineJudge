#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
char maz[25][25];
int k, p, r, c;
int a[15], b[15], cost[1<<11];
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};
int sx, sy;
bool visit[25][25][1<<11];

struct pos {
	int x, y, cost, collect;
	pos() {}//¹¹Ôìº¯Êý
	pos(int a, int b, int c, int d) {
		x = a, y = b, cost = c, collect = d;
	}
	bool operator< (const pos &a) const {
		return cost > a.cost;
	}
};

bool check(int x, int y) {
	return x >= 0 && x < r && y >= 0 && y < c;
}

int bfs() {
	priority_queue<pos> que;
	memset(visit, false, sizeof(visit));
	que.push(pos(sx, sy, 0, 0));
	visit[sx][sy][0] = true;
	while(!que.empty()) {
		pos now = que.top();
		que.pop();
		int x = now.x, y = now.y, collect = now.collect, ncost = now.cost + cost[collect] + 1;
		if(ncost > p) continue;
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if(!check(nx, ny) || maz[nx][ny] == '#' || visit[nx][ny][collect]) continue;
			if(nx == sx && ny == sy) {
				if(collect == (1 << k) - 1) return ncost;
				continue;
			}
			if(maz[nx][ny] <= 'Z' && maz[nx][ny] >= 'A') {
				int t = maz[nx][ny] - 'A';
				if((collect & (1 << t)) == 0) {
					que.push(pos(nx, ny, ncost + a[t], collect | (1<<t)));
					visit[nx][ny][collect|(1<<t)] = true;
				}
			}
			que.push(pos(nx, ny, ncost, collect));
			visit[nx][ny][collect] = true;
		}
	}
	return -1;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d\n", &r, &c, &k, &p);
		for(int i = 0; i < r; i++) {
			for(int j = 0; j <= c; j++) {
				scanf("%c", &maz[i][j]);
				if(maz[i][j] == '*') sx = i, sy = j;
			}
		}
		for(int i = 0; i < k; i++) scanf("%d%d", &a[i], &b[i]);
		memset(cost, 0, sizeof(cost));
		for(int t = 0; t < (1 << k); t++)
			for(int j = 0; j < k; j++)
				if(t & (1 << j)) cost[t] += b[j];
		int ans = bfs();
		if(ans == -1) printf("Impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}