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
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 30;
int n, cnt;
int maz[105][105];

void floyd() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(maz[i][k] != inf && maz[k][j] != inf) maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
            }
        }
    }
}

void solve() {
    floyd();
    int ans = inf, idx = -1;
    for(int i = 1; i <= n; i++) {
        int res = -1;
        for(int j = 1; j <= n; j++) {
            res = max(maz[i][j], res);
        }
        if(ans > res) ans = res, idx = i;
    }
    if(ans != inf) printf("%d %d\n", idx, ans);
    else printf("disjoin\n");
    return;
}

int main() {
    while(~scanf("%d", &n)) {
        if(!n) break;
        fill(&maz[0][0], &maz[105][105], inf);
        for(int u = 1; u <= n; u++) {
            scanf("%d", &cnt);
            maz[u][u] = 0;
            for(int i = 0; i < cnt; i++) {
                int v, w;
                scanf("%d%d", &v, &w);
                maz[u][v] = w;
            }
        }
        solve();
    }
    return 0;
}
