#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;
#define maxn 50005
int val[maxn], n, q;
int Min[maxn][20], Max[maxn][20];
void INIT_RMQ() {
	for(int i = 1; i <= n; i++)
		Min[i][0] = Max[i][0] = val[i];
	for(int i = 1;(1 << i) <= n;i++) {
		for(int j = 1; j + (1 << (i - 1)) <= n; j++) {
			Min[j][i] = min(Min[j][i-1], Min[j + (1 << (i-1))][i-1]);
			Max[j][i] = max(Max[j][i-1], Max[j + (1 << (i-1))][i-1]);
		}
	}
}

int MIN_RMQ(int l, int r, int k) {
	return min(Min[l][k], Min[r - (1<<k) + 1][k]);
}

int MAX_RMQ(int l, int r, int k) {
	return max(Max[l][k], Max[r - (1<<k) + 1][k]);
}

int solve(int l, int r) {
	int k = log(r - l + 1.0) / log(2.0); 
	return MAX_RMQ(l, r, k) - MIN_RMQ(l, r, k);
}

int main() {
	cin >> n >> q;
	int l, r;
	for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
	INIT_RMQ();
	for(int i = 1; i <= q; i++) {
		scanf("%d%d", &l, &r);
		printf("%d\n", solve(l, r));
	}
	return 0;
}