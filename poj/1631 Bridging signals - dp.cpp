#include "iostream"
using namespace std;
#define maxn 40005
int a[maxn], b[maxn], tot;

int b_search(int q) {
	int l = 0, r = tot;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(b[mid] == q) return mid;
		else if(b[mid] < q) l = mid + 1;
		else r = mid - 1;
	}
	return l;
}

int main() {
	int t, n, i;
	cin >> t;
	while(t--) {
		cin >> n;
		tot = 0;
		for(i = 0; i < n; i++)
			cin >> a[i];
		for(i = 0; i < n; i++) {
			if(b[tot] <= a[i])
				b[++tot] = a[i];
			else {
				int pos =  b_search(a[i]);
				b[pos] = a[i];
			}
		}
		cout << tot << endl;
	}
	return 0;
}