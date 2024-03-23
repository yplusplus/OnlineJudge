#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
#include "functional"
#include "string"
using namespace std;
int n, k;
void solve() {
	int val;
	string s;
	priority_queue<int, vector<int>, greater<int> > que;
	for(int i = 0; i < n; i++) {
		cin >> s;
		if(s[0] == 'I') {
			scanf("%d", &val);
			que.push(val);
			if(que.size() > k) que.pop();
		} else cout << que.top() << endl;
	}
}

int main() {
	while(~scanf("%d%d", &n, &k)) solve();
	return 0;
}