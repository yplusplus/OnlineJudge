#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define MAX 10
const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
int r, c;
int visit[MAX][MAX];
struct node {
	int x, y;
}s, t;

bool check(node now) {
	if(now.x >= 1 && now.x <= 8 && now.y >= 1 && now.y <= 8) return true;
	return false;
}

int bfs() {
	queue<node> que;
	que.push(s);
	visit[s.x][s.y] = 1;
	while(!que.empty()) {
		node now = que.front(), next;
		que.pop();
		if(now.x == t.x && now.y == t.y) return visit[t.x][t.y] - 1;
		for(int i = 0; i < 8; i++) {
			next.x = now.x + dx[i], next.y = now.y + dy[i];
			if(check(next) && !visit[next.x][next.y]) {
				visit[next.x][next.y] = visit[now.x][now.y] + 1;
				que.push(next);
			}
		}
	}
	return -1;
}

int main() {
	char ch1, ch2;
	int a, b;
	while(~scanf("%c%d %c%d\n", &ch1, &a, &ch2, &b)) {
		s.y = ch1 - 'a' + 1, s.x = a, t.y = ch2 - 'a' + 1, t.x = b;
		for(int i = 0; i < MAX; i++) memset(visit[i], 0, sizeof(visit[i]));
		printf("To get from %c%d to %c%d takes %d knight moves.\n", s.y + 'a' - 1, s.x, t.y + 'a' - 1, t.x, bfs());
	} 
	return 0;
}