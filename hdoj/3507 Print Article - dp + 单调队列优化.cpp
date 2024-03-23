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
int n, m;
int loc[maxn], head, tail;
ll sum[maxn], dp[maxn], cmp[maxn];
int main() {
    while(~scanf("%d%d", &n, &m)) {
        head = tail = 0, sum[0] = 0, dp[0] = 0;
        loc[tail++] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &sum[i]);
            sum[i] += sum[i-1];
        }
        for(int i = 1; i <= n; i++) {
            while(head + 1 < tail && (cmp[loc[head+1]] - cmp[loc[head]]) <= 2 * sum[i] * (sum[loc[head+1]] - sum[loc[head]])) head++;
            int j = loc[head];
            dp[i] = dp[j] + (sum[i] - sum[j]) * (sum[i] - sum[j]) + m;
            cmp[i] = dp[i] + sum[i] * sum[i];
            while(head + 1 < tail && (cmp[loc[tail-1]] - cmp[loc[tail-2]]) * (sum[i] - sum[loc[tail-1]]) >= (cmp[i] - cmp[loc[tail-1]]) * (sum[loc[tail-1]] - sum[loc[tail-2]])) tail--;
            loc[tail++] = i;
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}
