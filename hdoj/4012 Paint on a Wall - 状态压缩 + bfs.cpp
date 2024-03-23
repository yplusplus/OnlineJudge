#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
int visit[1<<16];
char maz[20];
int n;

int bfs() {
	queue<int> que;
	que.push(0);
	memset(visit, 0, sizeof(visit));
	visit[0] = 1;
	while(!que.empty()) {
		int now = que.front(), next;
		que.pop();
		if(now == (1<<(n<<1)) - 1) return visit[now] - 1;
		for(int i = 0; i < (n<<1); i++) {
			next = now;
			for(int j = i; j < (i/n+1)*n; j++) {
				if(next & (1<<j)) break;
				if(maz[j] == maz[i]) next |= (1<<j);
			}
			for(int j = i - 1; j >= (i/n)*n; j--) {
				if(next & (1<<j)) break;
				if(maz[j] == maz[i]) next |= (1<<j);
			}
			if(!visit[next]) {
				visit[next] = visit[now] + 1;
				que.push(next);
			}
			if(i/n) continue;
			next = now;
			if(next & (1<<(i+n))) continue;
			for(int j = i; j < n; j++) {
				if((next & (1<<j)) | (next & (1<<(j+n)))) break;
				if(maz[j] == maz[i]) next |= (1<<j);
				if(maz[j+n] == maz[i]) next |= (1<<(j+n));
			}
			for(int j = i - 1; j >= 0; j--) {
				if((next & (1<<j)) | (next & (1<<(j+n)))) break;
				if(maz[j] == maz[i]) next |= (1<<j);
				if(maz[j+n] == maz[i]) next |= (1<<(j+n));
			}
			if(!visit[next]) {
				visit[next] = visit[now] + 1;
				que.push(next);
			} 
		}
	}
	return -1;
}
int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		scanf("%s", maz);
		scanf("%s", maz + n);
		int ans = bfs();
		printf("Case #%d: %d\n", Case++, ans);
	}
	return 0;
}
