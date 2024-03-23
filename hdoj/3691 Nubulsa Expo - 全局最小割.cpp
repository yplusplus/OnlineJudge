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
#define maxn 510
const int inf = 1 << 27;
int maz[maxn][maxn];
int n, m, s;
int StoerWagner(int n) {//n为结点个数
    int cnt = n, s, t;
    int cut = inf;
    bool visit[maxn], use[maxn];
    int dist[maxn];
    memset(use, false, sizeof(use));//是否已合并
    while(--cnt > 0) {
        memset(visit, false, sizeof(visit));//是否加入A集合
        memset(dist, 0, sizeof(dist));//A外的元素与A元素的权值和
        int u = 0;
        while(use[u]) u++;
        visit[u] = true;
        for(int v = 0; v < n; v++)
            if(!use[v] && !visit[v])
                dist[v] = maz[v][u];
        s = t = u;
        for(int i = u; i < n; i++) {
            int max = 0, idx = u;
            for(int j = 0; j < n; j++)
                if(!use[j] && !visit[j] && dist[j] > max)
                    max = dist[idx = j];
            if(!max) break;
            visit[idx] = true;
            for(int j = 0; j < n; j++)
                if(!use[j] && !visit[j])
                    dist[j] += maz[j][idx];
            s = t, t = idx;
        }
        cut = min(cut, dist[t]);
        use[t] = true;
        for(int i = 0; i < n; i++)
            if(!use[i]) {
                maz[s][i] += maz[t][i];
                maz[i][s] += maz[i][t];
            }

    }
    return cut;
}

int main() {
    while(~scanf("%d%d%d", &n, &m, &s)) {
        if(!n) break;
        memset(maz, 0, sizeof(maz));
        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            a--, b--;
            maz[a][b] += c;
            maz[b][a] += c;
        }
        int ans = StoerWagner(n);
        cout << ans << endl;
    }
    return 0;
}
