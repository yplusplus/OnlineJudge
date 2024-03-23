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
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 500050
int n, k;
int loc[maxn], head, tail;
ll dp[maxn], val[maxn], dq[maxn], sum[maxn];
ll cmp[maxn];

ll calc2(int a, int b) {
    return val[a+1] - val[b+1];
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        sum[0] = 0, head = tail = 0, dp[0] = 0;
        loc[tail++] = 0, cmp[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &val[i]);
            sum[i] = val[i] + sum[i-1];
        }
        for(int i = 1; i <= n; i++) {
            while(head + 1 < tail && (cmp[loc[head+1]] - cmp[loc[head]]) <= i * calc2(loc[head+1], loc[head])) head++;
            int j = loc[head];
            dp[i] = dp[j] + sum[i] - sum[j] - (i - j) * val[j+1];
            cmp[i] = dp[i] - sum[i] + i * val[i+1];            
            if(i + 1 >= 2 * k) {
                while(head + 1 < tail && (cmp[loc[tail-1]] - cmp[loc[tail-2]]) * calc2(i - k + 1, loc[tail-1]) >= (cmp[i - k + 1] - cmp[loc[tail-1]]) * calc2(loc[tail-1], loc[tail-2])) tail--;
                loc[tail++] = i - k + 1;
            }
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}
