#include "iostream"
#include "cstring"
#include "algorithm"
using namespace std;
#define maxn 1005
#define maxm 1005
#define maxk 1000005
#define lowbit(i) i & (-i)
struct highway {
	int x, y;
}a[maxk];
int c[maxn], n, m, k;

bool cmp(const highway &a, const highway &b) {
	if(a.y != b.y) return a.y > b.y;
	return a.x > b.x;
}

void update(int i, int v) {
	for(; i < maxn; i += lowbit(i)) c[i] += v;
}

int sum(int i) {
	int res = 0;
	for(; i; i -= lowbit(i)) res += c[i];
	return res;
}

int main() {
	int tn, i;
	__int64 ans;
	scanf("%d", &tn);
	int t = 1;
	while(t <= tn) {
		memset(c, 0, sizeof(c));
		scanf("%d%d%d", &n, &m, &k);
		for(i = 0; i < k; i++) 
			scanf("%d%d", &a[i].x, &a[i].y);
		sort(a, a + k, cmp);
		for(i = ans = 0; i < k; i++) {
			ans += sum(a[i].x-1);
			update(a[i].x, 1);
		}
		printf("Test case %d: %I64d\n", t++, ans);
	}
	return 0;
}