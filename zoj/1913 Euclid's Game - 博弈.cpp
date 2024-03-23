#include "iostream"
#include "cstdio"
using namespace std;
int n, m;
int main(){
	while(1) {
		cin >> n >> m;
		if(!n && !m) break;
		int cnt = 0;
		while(n && m) {
			cnt++;
			if(n < m) {
				int t = n;
				n = m;
				m = t;
			}
			if(n - m >= m) break;
			n -= m;
		}
		if(cnt % 2) printf("Stan wins\n");
		else printf("Ollie wins\n");
	}
	return 0;
}