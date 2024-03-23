#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 111111;
int a[N], n;

int check(int a[], int s) {
    for (int i = 0; i < n; i++) {
        if (s < a[i]) return 1;
        else if (s == a[i]) s--;
    }
    return 0;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int pre = 0;
        for (int i = 0; i < n; i++) {
            int height;
            scanf("%d", &height);
            a[i] = height - pre;
            pre = height;
        }
        int ans = *max_element(a, a + n);
        ans += check(a, ans);
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}
