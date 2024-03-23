#include "iostream"
#include "cstdio"
using namespace std;

int n, m;
void swap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}
int main() {
	while(1) {
		cin >> n >> m;
		if(!n && !m) break;
		int cnt = 0;
		while(n && m) {
			cnt++;
			if(n < m) swap(n, m);
			if(n / m > 1) break;
			else n -= m;
		}
		if(cnt % 2) cout << "Stan wins" << endl;
		else cout << "Ollie wins" << endl;
	}
	return 0;
}