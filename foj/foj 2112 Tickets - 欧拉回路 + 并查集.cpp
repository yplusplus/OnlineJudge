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
int n, m;
int cnt[N], num[N], fa[N];
bool has[N];
void init(int n) {
    for(int i = 0; i <= n; i++) {
        fa[i] = i;
        cnt[i] = 0;
        num[i] = 0;
        has[i] = false;
    }
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) false;
    fa[a] = b;
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init(n);
        for(int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            cnt[a]++;
            cnt[b]++;
            has[a] = true;
            has[b] = true;
            Union(a, b);
        }
        for(int i = 1; i <= n; i++)
            if(cnt[i] & 1) num[find(i)]++;
        int rec[N], tot = 0;
        for(int i = 1; i <= n; i++) {
            if(has[i] && fa[i] == i) rec[tot++] = num[i];
        }
        int cur = rec[0];
        int ans = 0;
        for(int i = 1; i < tot; i++) {
            if(cur > 0 && rec[i] > 0) cur += rec[i] - 2, ans++;
            else if(cur == 0 && rec[i] == 0) cur = 2, ans++;
            else cur += rec[i], ans++;
        }
        if(cur > 0) ans += (cur - 2) >> 1;
        printf("%d\n", ans);
    }
    return 0;
}
