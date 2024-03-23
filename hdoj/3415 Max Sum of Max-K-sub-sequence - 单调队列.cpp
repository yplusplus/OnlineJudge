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
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 100050
const int inf = 1 << 30;
int que[maxn<<1], head, tail;
int sum[maxn<<1];
int val[maxn];
int n, k;
int ans, s, t;
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        sum[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            sum[i] = val[i] + sum[i-1];
        }
        for(int i = n + 1; i <= 2 * n; i++) {
            sum[i] = sum[i-1] + val[i-n];
        }
        ans = -inf;
        head = tail = 0;
        que[tail++] = 0;
        for(int i = 1; i <= 2 * n; i++) {
            while(head < tail && que[head] < i - k) head++;
            if(ans < sum[i] - sum[que[head]]) {
                ans = sum[i] - sum[que[head]];
                s = que[head] + 1, t = i;
            }
            while(head < tail && sum[que[tail-1]] > sum[i]) tail--;
            que[tail++] = i;
        }
        if(s > n) s -= n;
        if(t > n) t -= n;
        cout << ans << " " << s << " " << t << endl;
    }
    return 0;
}
