#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 200050
int cnt[10010], a[maxn];
int n, m;
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        scanf("%d", &m);
        while(m--) {
            int l, r;
            scanf("%d%d", &l, &r);
            if(r - l > 10002) {
                printf("0\n");
                continue;
            }
            memset(cnt, 0, sizeof(cnt));
            for(int i = l; i <= r; i++) {
                cnt[a[i]]++;
            }
            int p = -1, q = inf;
            for(int i = 1; i <= 10000; i++) {
                if(cnt[i] == 0) continue;
                if(cnt[i] > 1) {
                    q = 0;
                    break;
                } else if(p != -1) {
                    q = min(q, i - p);
                }
                p = i;
            }
            printf("%d\n", q);
        }
    }
    return 0;
}
