#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

#define ll long long
const int N = 55;
ll p;
int n, l1, l2;
ll bin[N][N];

//Ai 为n个球有i个黑球的事件
//B 摸出l1+l2个球，其中有l1个黑球的事件
//P(Ai | B) = P(Ai B) / P(B)
//          = P(B | Ai) * P(Ai) / [∑P(B | Ak) * P(Ak)], k = l1, l1 + 1, ... , n - l2
//因为题目说了有k个黑球是等概率的，即P(A0) = P(A1) = ... = P(An);
//          = P(B | Ai) / ∑P(B | Ak), k = l1, l1 + 1, ... , n - l2
//P(B | Ai) = C[i][l1] * C[n-i][l2] / C[n][l1+l2]
//此题要用整数判断，不然精度不够！！！！

void init() {
	for (int i = 0; i < N; i++) {
		bin[i][0] = bin[i][i] = 1;
		for (int j = 1; j < i; j++) {
			bin[i][j] = bin[i - 1][j - 1] + bin[i - 1][j];
		}
	}
}

ll a[N];
int main() {
	init();
	while (cin >> n >> l1 >> l2 >> p) {
		memset(a, 0, sizeof(a));
		if (l1 + l2 == n) {
			a[l1] = 100;
		} else {
			ll sum = 0;
			for (int i = l1; i <= n - l2; i++) {
				sum += bin[i][l1] * bin[n - i][l2];
			}
			for (int i = l1; i <= n - l2; i++) {
				a[i] = bin[i][l1] * bin[n - i][l2] * 100;
			}
			p *= sum;
		}
		int pos = 0, len = n + 1;
		for (int i = 0; i <= n; i++) {
			ll tmp = 0;
			int j;
			for (j = i; j <= n; j++) {
				tmp += a[j];
				if (tmp >= p) break;
			}
			if (tmp >= p && j - i + 1 < len) pos = i, len = j - i + 1;
		}
		cout << pos << " " << pos + len - 1 << endl;
	}
	return 0;
}

