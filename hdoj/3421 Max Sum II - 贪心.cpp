#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1111111;
int n;
int a[N];
int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        if (Case > 1) puts("");
        scanf("%d", &n);
        int ans = 0;
        int tmp = 0;
        int step = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            if (a[i] >= 0) {
                ans += a[i];
                tmp += a[i];
            } else {
                if (tmp > 0) step++;
                tmp = 0;
            }
        }
        if (tmp > 0) step++;
        printf("Case %d:\n", Case++);
        printf("%d %d\n", step, ans);
    }
    return 0;
}
