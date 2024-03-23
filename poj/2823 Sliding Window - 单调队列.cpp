#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 1000500
int n, k, val;
int maxx[maxn], minn[maxn];
int head1, tail1, head2, tail2, tot;
struct Drab {
	int val, idx;
	Drab(){}
	Drab(int _val, int _idx) {
		val = _val, idx = _idx;
	}
}que1[maxn], que2[maxn];

void init() {
	tot = 0;
	head1 = tail1 = head1 = tail1 = 0;
}

void push1(int val, int idx) {
	while(head1 < tail1 && que1[tail1 - 1].val > val) tail1--;
	que1[tail1++] = Drab(val, idx);
}

void push2(int val, int idx) {
	while(head2 < tail2 && que2[tail2 - 1].val < val) tail2--;
	que2[tail2++] = Drab(val, idx);
}

int main() {
	while(~scanf("%d%d", &n, &k)) {
		init();
		for(int i = 0; i < n; i++) {
			scanf("%d", &val);
			push1(val, i), push2(val, i);
			if(i >= k - 1) {
				if(que1[head1].idx <= i - k) head1++;
				minn[tot] = que1[head1].val;
				if(que2[head2].idx <= i - k) head2++;
				maxx[tot] = que2[head2].val;
				tot++;
			}
		}
		for(int i = 0; i < tot; i++) printf("%d ", minn[i]);
		printf("\n");
		for(int i = 0; i < tot; i++) printf("%d ", maxx[i]);
		printf("\n");
	}
	return 0;
}