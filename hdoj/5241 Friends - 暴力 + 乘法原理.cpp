#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD = 10000000;
const int N = 700;

struct BigNum {
    int a[N], len;
    BigNum() { memset(a, 0, sizeof(a)); len = 0; }
    BigNum(int x) { memset(a, 0, sizeof(a)); a[0] = x; len = 0; }
    void operator *=(const int & v) {
        for (int i = 0; i <= len; i++) {
            a[i] *= v;
        }
        for (int i = 0; i < N - 1; i++) {
            if (a[i] >= MOD) {
                a[i + 1] += a[i] / MOD;
                a[i] %= MOD;
            }
        }
        for (int i = N - 1; i >= 0; i--) {
            if (a[i]) {
                len = i;
                break;
            }
        }
        //printf("len :%d\n", len);
    }
    void Print() {
        printf("%d", a[len]);
        for (int i = len - 1; i >= 0; i--) printf("%07d", a[i]);
        printf("\n");
    }
} ans[3333];

int main() {
    ans[0] = BigNum(1);
    for (int i = 1; i <= 3000; i++) {
        ans[i] = ans[i - 1];
        ans[i] *= 32;
    }
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("Case #%d: ", Case++);
        ans[n].Print();
    }
    return 0;
}
