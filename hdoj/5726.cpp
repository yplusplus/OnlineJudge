#include <iostream>
#include <cmath>
#include <map>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 111111;
const int M = 20;

int a[N];
int gcd[N][20];
map<int, long long> cnt;
int n;

void init_gcd() {
    for (int i = 1; i <= n; i++) {
        gcd[i][0] = a[i];
    }
    for (int i = 1; (1 << i) <= n; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            gcd[j][i] = __gcd(gcd[j][i - 1], gcd[j + (1 << i - 1)][i - 1]);
        }
    }
}

int get_gcd(int a, int b) {
    if (a > b) swap(a, b);
    int k = log(b - a + 1) / log(2.0);
    return __gcd(gcd[a][k], gcd[b - (1 << k) + 1][k]);
}

void calc() {
    cnt.clear();
    for (int i = 1; i <= n; i++) {
        int prev = i - 1;
        while (prev < n) {
            int lt = prev + 1, rt = n;
            int d = get_gcd(i, lt);
            int idx = lt;
            while (lt <= rt) {
                int mid = (lt + rt) / 2;
                if (get_gcd(i, mid) >= d) {
                    lt = mid + 1;
                    idx = mid;
                } else {
                    rt = mid - 1;
                }
            }
            //cout << i << " " << idx << " " << d << " " << (idx - prev) << endl;
            cnt[d] += (idx - prev);
            prev = idx;
        }
    }
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        init_gcd();
        calc();
        int q;
        scanf("%d", &q);
        printf("Case #%d:\n", Case++);
        for (int i = 0; i < q; i++) {
            int L, R;
            scanf("%d%d", &L, &R);
            int d = get_gcd(L, R);
            cout << d << " " << cnt[d] << endl;
        }
    }
    return 0;
}
