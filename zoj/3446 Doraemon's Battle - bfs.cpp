#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
#include "cmath"
using namespace std;
#define MAX 105
int lh, ls, n;
int d[MAX];
int visit[255][105][45];
int add;

struct st {
    int hp, sp, cnt;
    void init(int a, int b, int c) {
        if(a > lh) a = lh;
		if(b > ls) b = ls;
		hp = a, sp = b, cnt = c;
    }
} start;

int bfs() {
    queue<st> que;
    que.push(start);
    visit[start.hp][start.sp][start.cnt] = 1;
    while (!que.empty()) {
        st now = que.front(), next;
        que.pop();
		//第一种操作
        next.init(now.hp - (now.cnt - 1), now.sp + 1 + (now.cnt - 1) % 3, (now.cnt - 1));
		if (next.cnt <= 0) return visit[now.hp][now.sp][now.cnt];
        if (next.hp > 0 && !visit[next.hp][next.sp][next.cnt]) {
            visit[next.hp][next.sp][next.cnt] = visit[now.hp][now.sp][now.cnt] + 1;
            que.push(next);
        }
		//第二种操作
        next.init(now.hp + add - now.cnt, now.sp + now.cnt % 3, now.cnt);
        if (next.hp > 0 && !visit[next.hp][next.sp][next.cnt]) {
            visit[next.hp][next.sp][next.cnt] = visit[now.hp][now.sp][now.cnt] + 1;
            que.push(next);
        }
		//第三种操作
        if (now.sp > 0) {
			if(now.cnt - d[now.sp] <= 0) return visit[now.hp][now.sp][now.cnt];
            next.init(now.hp - (now.cnt - d[now.sp]), (now.cnt - d[now.sp]) % 3, (now.cnt - d[now.sp]));
            if (next.hp > 0 && !visit[next.hp][next.sp][next.cnt]) {
                visit[next.hp][next.sp][next.cnt] = visit[now.hp][now.sp][now.cnt] + 1;
                que.push(next);
            }
		}
    }
    return -1;
}

void init() {
	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 105; j++)
			for (int k = 0; k < 45; k++)
				visit[i][j][k] = 0;
	add = (int) floor(0.2 * lh);
}

int main() {
	while (~scanf("%d%d%d", &lh, &ls, &n)) {
		for (int i = 1; i <= ls; i++) scanf("%d", &d[i]);
		start.init(lh, 0, n);
		init();
		int ans = bfs();
		if (ans == -1) printf("HELP!\n");
		else printf("%d\n", ans);
	}
	return 0;
}