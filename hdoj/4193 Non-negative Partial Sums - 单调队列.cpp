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
#define maxn 1000050
int n;
int val[maxn];
int sum[maxn<<1];
int que[maxn<<1], head, tail;

int main() {
    while(~scanf("%d", &n)) {
        if(!n) break;
        sum[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            sum[i] = sum[i-1] + val[i];
        }
        for(int i = n + 1; i <= 2 * n; i++) {
            sum[i] = sum[i-1] + val[i-n];
        }
        int ans = 0;
        head = tail = 0;
        que[tail++] = 0;
        for(int i = 1; i <= 2 * n; i++) {
            if(i > n) {
                while(head < tail && que[head] < i - n - 1) head++;
                if(sum[que[head]] >= sum[i-n-1]) ans++;
            }
            while(head < tail && sum[que[tail-1]] > sum[i]) tail--;
            que[tail++] = i;
        }
        cout << ans << endl;
    }

    return 0;
}
