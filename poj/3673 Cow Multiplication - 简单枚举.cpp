#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define MAX 15
char a[MAX], b[MAX];

int main() {
    while(~scanf("%s%s", a, b)) {
        int alen = strlen(a), blen = strlen(b);
        int ans = 0;
        for(int i = 0; i < alen; i++) {
            for(int j = 0; j < blen; j++) {
                ans += (a[i] -'0') * (b[j] - '0');
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
