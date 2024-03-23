#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 50050
int fa[maxn];
int n, m;
void init() {
	for(int i = 0; i < maxn; i++) fa[i] = i;
}

int Find(int x) {
	if(x != fa[x]) fa[x] = Find(fa[x]);
	return fa[x];
}

bool Union(int x, int y) {
	x = Find(x), y = Find(y);
	if(x == y) return false;
	fa[x] = y;
	return true; 
}

int main() {
	int a, b, Case = 1;
	while(~scanf("%d%d", &n, &m)) {
		if(!n && !m) break;
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			Union(a, b);
		}
		int cnt = 0;
		for(int i = 1; i <= n; i++)
			if(fa[i] == i) cnt++;
		printf("Case %d: %d\n", Case++, cnt);
	}
	return 0;
}