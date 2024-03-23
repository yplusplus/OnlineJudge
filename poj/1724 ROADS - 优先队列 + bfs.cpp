#include "cstdio"
#include "cstring"
#include "iostream"
#include "queue"
using namespace std;
#define maxn 105
#define maxm 20000
int eh[maxn], tot;
int k, n, m;

struct stt {
	int u, l, t;
	stt() {};
	stt(int a, int b, int c) {
		u = a, l = b, t = c;
	}
	bool operator< (const stt &a) const {
		return l > a.l;
	}
};

struct Edge {
	int u, v, l, t, next;
}et[maxm];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int l, int t) {
	Edge e = {u, v, l, t, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

int bfs() {
	priority_queue<stt> que;
	que.push(stt(1, 0, 0));
	while(!que.empty()) {
		stt now = que.top();
		que.pop();
		if(now.u == n) return now.l;
		for(int i = eh[now.u]; i != -1; i = et[i].next)
			if(now.t + et[i].t <= k)
				que.push(stt(et[i].v, now.l + et[i].l, now.t + et[i].t));
	}
	return -1;
}
int main() {
	scanf("%d%d%d", &k, &n, &m);
	init();
	for(int i = 0; i < m; i++) {
		int u, v, l, t;
		scanf("%d%d%d%d", &u, &v, &l, &t);
		addedge(u, v, l, t);
	}
	int ans = bfs();
	printf("%d\n", ans);
	return 0;
}