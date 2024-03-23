#include "iostream"
#include "algorithm"
#include "cstring"
using namespace std;
#define maxn 100005
#define maxm 50005
#define lowbit(x) x & (-x)
int n, m;
int a[maxn], b[maxn], c[maxn];
int ans[maxm];

struct query {
	int x, y, k, id;
}q[maxm];

int min(int a, int b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

bool cmp(const query &a, const query &b) {
	if(a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

void update(int i, int v) {
	for(; i < maxn; i += lowbit(i)) c[i] += v;
}

int b_search(int q) {
	int l = 0, r = n;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(b[mid] > q) r = mid - 1;
		else if(b[mid] < q) l = mid + 1;
		else return mid + 1;
	}
}

int find_kth(int k) {
	int cnt = 0, sum = 0;
	for(int i = 20; i >= 0; i--) {
		sum += (1 << i);
		if(sum > maxn || cnt + c[sum] >= k) sum -= (1 << i);
		else cnt += c[sum];
	}
	return sum + 1;
}

int main() {
	int i;
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b[i-1] = a[i];
	}
	sort(b, b + n);
	for(i = 0; i < m; i++) {
		scanf("%d%d%d", &q[i].x, &q[i].y, &q[i].k);
		q[i].id = i;
	}
	sort(q, q + m, cmp);
	memset(c, 0, sizeof(c));
	for(i = 0; i < m; i++) {
		int j;
		if(i == 0) for(j = q[i].x; j <= q[i].y; j++) update(b_search(a[j]), 1);
		else {
			for(j = q[i-1].x; j < min(q[i].x, q[i-1].y + 1); j++) update(b_search(a[j]), -1);
			for(j = max(q[i].x, q[i-1].y + 1); j <= q[i].y; j++) update(b_search(a[j]), 1);
		}
		ans[q[i].id] = find_kth(q[i].k);
	}
	for(i = 0; i < m; i++) 
		printf("%d\n", b[ans[i]-1]);
	return 0;	
}	