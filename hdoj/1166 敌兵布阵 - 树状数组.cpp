#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
using namespace std;
#define pb push_back
#define maxn 50005
#define lowbit(x) (x & (-x))
int val[maxn], n;

void add(int x, int e) {
    for(int i = x; i < maxn; i += lowbit(i)) {
        val[i] += e;
    }
}

int sum(int x) {
    int res = 0;
    for(int i = x; i; i -= lowbit(i)) {
        res += val[i];
    }
    return res;
}

int main() {
    int T, Case = 1, e, a, b;
    char str[10];
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        memset(val, 0, sizeof(val));
        for(int i = 1; i <= n; i++) {
            scanf("%d", &e);
            add(i, e);
        }
        printf("Case %d:\n", Case++);
        while(1) {
            scanf("%s", str);
            if(str[0] == 'E') break;
            else {
                scanf("%d%d", &a, &b);
                if(str[0] == 'Q') printf("%d\n", sum(b) - sum(a - 1));
                else if(str[0] == 'A') add(a, b);
                else add(a, -b);
            }
        }
    }
    return 0;
}

