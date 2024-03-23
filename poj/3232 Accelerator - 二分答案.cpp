#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "functional"
using namespace std;
#define maxn 100005
int n, m, k;
int d[maxn];
bool solve(long long ans) {
	long long sum = m * ans, tmp;
	if(k == 1) return d[0] <= ans;
	for(int i = 0; i < n; i++) {
		if(d[i] - ans <= 0) return true; 
		tmp = (d[i] - ans) / (k - 1);
		if(((d[i] - ans) % (k - 1)) != 0) tmp++;
		if(tmp > ans) return false;
		sum -= tmp;
		if(sum < 0) return false;
	}
	return true;
}

long long binary() {
	long long l = 0, r = d[0], res = -1;
	while(l <= r) {
		long long mid = (l + r) >> 1;
		if(solve(mid)) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d", &d[i]);
		sort(d, d + n, greater<int>());
		scanf("%d%d", &m, &k);
		printf("%lld\n", binary());
	}
	return 0;
}
