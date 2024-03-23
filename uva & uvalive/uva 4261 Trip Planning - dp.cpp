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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 1100
const ll linf = 1LL << 50;
int n;
ll sum[maxn], dp[maxn];
int p[maxn], num[maxn];
int main() {
    bool flag = false;
    while(~scanf("%d", &n), n) {
        if(flag) puts("");
        else flag = true;
        sum[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &sum[i]);
            sum[i] += sum[i-1];
        }
        dp[0] = 0;
        num[0] = 0;
        memset(p, -1, sizeof(p));
        for(int i = 1; i <= n; i++) {
            dp[i] = linf;
            for(int j = 0; j < i; j++) {
                ll tmp = sum[i] - sum[j] - 100;
                ll res = dp[j] + tmp * tmp;
                if(dp[i] > res) {
                    dp[i] = res;
                    p[i] = j;
                    num[i] = num[j] + 1;
                } else if(dp[i] == res && num[j] < num[p[i]]) {
                    p[i] = j;
                    num[i] = num[j] + 1;
                }
            }
        }
        cout << "p=" << dp[n] << endl;
        int x = n, ans[maxn], tot = 0;
        while(x != -1) {
            ans[tot++] = x;
            x = p[x];
        }
        int cnt = 0;
        for(int i = tot - 1; i >= 0; i--) {
            printf(" %d", ans[i]);
            cnt++;
            if(cnt == 30) {
                printf("\n");
                cnt = 0;
            }
        }
        if(cnt) printf("\n");
    }
    return 0;
}
