#include "iostream"
#include "algorithm"
using namespace std;
#define maxn 100005
#define maxm 100005

struct Cow {
	int s, e, id;
}cow[maxm];

int c[maxm], n, cnt[maxn];
int m;
bool cmp(const Cow &a, const Cow &b) {
	if(a.e != b.e) return a.e > b.e;
	else return a.s < b.s;
}

int lowbit(int x) {
	return x & (-x);
}

void update(int x, int v) {
	for(int i = x; i <= m + 1; i += lowbit(i)) c[i] += v;
}

int sum(int x) {
	int res = 0;
	for(int i = x; i; i -= lowbit(i)) res += c[i];
	return res;
}

int main() {
	int i;
	while(cin >> n, n) {
		m = 0;
		memset(c, -0, sizeof(c));
		for(i = 1; i <= n; i++) {
			scanf("%d%d", &cow[i].s, &cow[i].e);
			cow[i].id = i;
			cnt[i] = 0;
			if(m < cow[i].s) m = cow[i].s;
		}
		sort(cow + 1, cow + 1 + n,cmp);
		for(i = 1; i <= n; i++) {
			if(i > 1 && cow[i].s == cow[i-1].s && cow[i].e == cow[i-1].e)
				cnt[cow[i].id] = cnt[cow[i-1].id];
			else cnt[cow[i].id] = sum(cow[i].s + 1);
			update(cow[i].s + 1, 1);
		}
		for(int i = 1; i < n; i++) cout << cnt[i] << " ";
		cout << cnt[n] << endl;
	}
	return 0;
}
