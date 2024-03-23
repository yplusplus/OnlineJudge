#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "queue"
using namespace std;
#define maxn 25500
int n, k;

struct trap {
	int t, d;
}traps[maxn];

bool cmp(const trap &a, const trap &b) {
	return a.d < b.d;
}

int solve() {
	priority_queue<int> que;
	int cost = 0, ti = 0;
	for(int i = 0; i < n; i++) {
		ti += traps[i].t;
		que.push(traps[i].t);
		while(ti > traps[i].d) {
			if(que.empty()) return -1;
			ti -= que.top();
			que.pop();
			if(++cost == k) return -1;
		}
	}
	return cost;
}

int main() {
	while(~scanf("%d%d", &n, &k)) {
		for(int i = 0; i < n; i++) scanf("%d%d", &traps[i].t, &traps[i].d);
		sort(traps, traps + n, cmp);
		printf("%d\n", solve());
	}
	return 0;
}