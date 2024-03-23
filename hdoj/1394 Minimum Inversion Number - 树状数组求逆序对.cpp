#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 5005
const int inf = 1 << 30;
int sum[maxn], n, val[maxn];

void update(int x) {
    for(int i = x; i < maxn; i += lowbit(i))
        sum[i]++;
}

int SUM(int x) {
    int res = 0;
    for(int i = x; i; i -= lowbit(i))
        res += sum[i];
    return res;
}

int main() {
    while(~scanf("%d", &n)) {
        memset(sum, 0, sizeof(sum)); 
        int ans = inf, tmp = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &val[i]);
            tmp += SUM(n) - SUM(val[i]);
            update(val[i]+1);
        }
        for(int i = 0; i < n - 1; i++) {
            tmp += n - 2 * val[i] - 1;
            ans = min(ans, tmp);
        }
        cout << ans << endl;
    }
    return 0;
}
