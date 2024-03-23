#include "iostream"
#include "cstdio"
#include "algorithm"
#include "cstring"
using namespace std;
#define maxn 100500
int n;
struct node {
	int d, t;
}a[maxn];

bool cmp(const node &a, const node &b) {
	if(a.t != b.t) return a.t > b.t;
	else return a.d > b.d;
}

int solve() {
	sort(a, a + n, cmp);
	int ti = 0, ans = 0;
	for(int i = 0; i < n; i++) {
		ans = max(ans, ti + a[i].d + a[i].t);
		ti += a[i].d;
	}
	return ans;
}

int main() {
	int T, Case = 1;;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d%d", &a[i].d, &a[i].t);
		}
		int ans = solve();
		printf("Case %d: %d\n", Case++, ans);
	}
	return 0;
}