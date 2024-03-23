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
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111111;

int cnt[N];//原序列
int Max[N][18]; //第2维是log(n)个数，小心开大了爆了内存
int n, q;
int start[N], end[N];
int a[N];
int pos[N << 1];
int Log[N];

void init() {
    for (int i = 0; i < N; i++) {
        Log[i] = (int)(log(i + 1) / log(2.0));
    }
}

void initRMQ() {
    for(int i = 1; i <= n; i++) Max[i][0] = cnt[i];
    for(int k = 1; (1<<k) <= n; k++) {
        for(int i = 1; i + (1<<k) - 1 <= n; i++) {
            Max[i][k] = max(Max[i][k-1], Max[i+(1<<(k-1))][k-1]);
        }
    }
}

int MaxRMQ(int a, int b) {
    int k = Log[b - a];
    return max(Max[a][k], Max[b-(1<<k)+1][k]);
}

int main() {
    init();
    while (~scanf("%d", &n), n) {
        scanf("%d", &q);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        int tot = 0;
        for (int i = 1; i <= n; i++) {
            if (i > 1 && a[i] == a[i - 1]) {
                cnt[tot]++;
            } else {
                tot++;
                cnt[tot] = 1;
                start[tot] = i;
                pos[a[i] + N] = tot;
            }
            end[tot] = i;
        }
        n = tot;
        initRMQ();
        int l, r;
        while (q--) {
            scanf("%d%d", &l, &r);
            if (a[l] == a[r]) {
                printf("%d\n", r - l + 1);
            } else {
                int ans = 0;
                int le = pos[a[l] + N];
                int ri = pos[a[r] + N];
                ans = max(ans, end[le] - l + 1);
                ans = max(ans, r - start[ri] + 1);
                le++, ri--;
                if (le <= ri) {
                    ans = max(ans, MaxRMQ(le, ri));
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
