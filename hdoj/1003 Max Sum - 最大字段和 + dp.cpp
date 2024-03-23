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
#define maxn 100050
int n;
int a[maxn], sum[maxn];
int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        sum[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            sum[i] = sum[i-1] + a[i];
        }
        int ans = 0, res = 0, idx = -1;
        for(int i = 1; i <= n; i++) {
            if(res + a[i] < 0) res = 0;
            else res += a[i];
            if(ans < res) ans = res, idx = i;
        }
        if(Case != 1) puts("");
        printf("Case %d:\n", Case++);
        if(ans == 0) {
            int *p = max_element(a + 1, a + n + 1);
            cout << *p << " " << p - a << " " << p - a << endl;
        } else {
            for(int i = 1; i < idx; i++) {
                if(sum[idx] - sum[i-1] == ans) {
                    cout << ans << " " << i << " " << idx << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
