#include "iostream"
#include "cstring"
using namespace std;

int cnt[920][8210], pre[920][8210], num[10];

void init() {
	int i, j, k;
	for(i = 0; i <= 900; i++)
		for(j =0; j <= 8100; j++)
			cnt[i][j] = pre[i][j] = 150;
	cnt[0][0] = 0;
	for(i = 0; i <= 900; i++) {
		for(j = i; j <= 8100; j++) {
			if(cnt[i][j] <= 100)
				for(k = 1; k <= 9; k++) {
					if(cnt[i + k][j + k * k] >= cnt[i][j] + 1) {
						cnt[i + k][j + k * k] = cnt[i][j] + 1;
						pre[i + k][j + k * k] = k;
					}
				}
		}
	}
}

int main() {
	int t, s1, s2;
	init();
	cin >> t;
	while(t--) {
		cin >> s1 >> s2;
		int i = s1, j = s2;
		if(s1 > 900 || s2 > 8100 || cnt[i][j] == 0 || cnt[i][j] > 100 ) {
			cout << "No solution" << endl;
			continue;
		}
		memset(num, 0, sizeof(num));
		for(; i != 0 || j != 0; ) {
			int k = pre[i][j];
			num[k]++;
			i -= k, j -= k * k;
		}
		for(int index = 1; index <= 9; index++) {
			while(num[index]--) cout << index;
		}
		cout << endl;
	}
	return 0;
}
			

