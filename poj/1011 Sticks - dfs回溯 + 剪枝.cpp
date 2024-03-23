#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "functional"
using namespace std;
#define maxn 65
int n, sum, goal;
int stick[maxn];
bool visit[maxn];

bool cmp(const int &a, const int &b) {
	return a > b;
}

bool dfs(int now, int index, int cnt) {
	if(goal * cnt == sum) return true;
	for(int i = index; i < n; i++) {
		if(visit[i] || (i && !visit[i-1] && stick[i] == stick[i-1])) continue;
		if(now + stick[i] == goal) {
			visit[i] = true;
			if(dfs(0, 0, cnt + 1)) return true;
			visit[i] = false;
			return false;
		} else if(now + stick[i] < goal) {
			visit[i] = true;
			if(dfs(now + stick[i], i + 1, cnt)) return true;
			visit[i] = false;
			if(now == 0) return false;
		}
	}
	return false;
}

int solve() {
	sort(stick, stick + n, cmp);
	for(goal = stick[0]; goal < sum; goal++) {
		if(sum % goal != 0) continue;
		memset(visit, false, sizeof(visit));
		if(dfs(0, 0, 0)) break;
	}
	return goal;
}

int main() {
	while(~scanf("%d", &n)) {
		if(!n) break;
		sum = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d", &stick[i]);
			sum += stick[i];
		}
		printf("%d\n", solve());
	}
	return 0;
}