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
#define maxn 550
int tot1, tot2;
bool maz[maxn][maxn], vist[maxn];//构图：如果i->j有边，maz[i][j] = 1;(区分:有向图,无向图)
int match[maxn], n, m;
bool dfs(int u) {
    for (int v = 1; v <= tot2; v++) {
        if (maz[u][v] && !vist[v]) {
            vist[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}
int Match() {//二分图匹配
    int cnt = 0;
    memset(match, -1, sizeof (match));
    for (int u = 1; u <= tot1; u++) {
        memset(vist, false, sizeof (vist));
        if (dfs(u)) cnt++; //每找到一条增广路，匹配数+1
    }
    return cnt; //返回最大匹配数
}

int main() {
    int T;
    scanf("%d", &T);
    int dog, cat, n;
    string a, b;
    pair<string, string> p1[550], p2[550];
    while(T--) {
        scanf("%d%d%d", &cat, &dog, &n);
        memset(maz, 0, sizeof(maz));
        tot1 = 0, tot2 = 0;
        for(int i = 1; i <= n; i++) {
            cin >> a >> b;
            if(a[0] == 'C') p1[++tot1] = mp(a, b);
            else p2[++tot2] = mp(a, b);
        }
        for(int i = 1; i <= tot1; i++) {
            for(int j = 1; j <= tot2; j++) {
                if(p1[i].fi == p2[j].se || p1[i].se == p2[j].fi) maz[i][j] = 1;
            }
        }
        int ans = n - Match();
        printf("%d\n", ans);
    }
    return 0;
}
