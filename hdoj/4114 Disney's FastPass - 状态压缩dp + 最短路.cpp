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
const int inf = 1 << 28;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 55
int n, m, k;
int dp[maxn][1<<8][1<<8];
bool visit[maxn][1<<8][1<<8];
int fp[maxn], hash[maxn];
int maz[maxn][maxn];
int t[10], ft[10];
struct State {
    int u, m1, m2;
    State(){}
    State(int _u, int _m1, int _m2) {
        u = _u, m1 = _m1, m2 = _m2;
    }
};
queue<State> que;

void floyd() {
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                maz[i][j] = min(maz[i][j], maz[i][k] + maz[k][j]);
}

void update(int u, int m1, int m2, int w) {
    if(dp[u][m1][m2] > w) {
        dp[u][m1][m2] = w;
        if(!visit[u][m1][m2]) {
            que.push(State(u, m1, m2));
            visit[u][m1][m2] = 1;
        }
    }
}

void solve() {
    while(!que.empty()) que.pop();
    memset(visit, false, sizeof(visit));
    int nn = 1 << k;
    for(int i = 0; i < n; i++)
       for(int j = 0; j < nn; j++)
          for(int kk = 0; kk < nn; kk++)
             dp[i][j][kk] = inf; 
    update(0, 0, fp[0], 0);
    while(!que.empty()) {
        State now = que.front();
        que.pop();
        int u = now.u, m1 = now.m1, m2 = now.m2;
        visit[u][m1][m2] = 0;
        for(int v = 0; v < n; v++) {
            if(hash[v] == 0 && fp[v] == 0 && v != 0) continue;
            int w = maz[u][v];
            int m22 = m2 | fp[v];
            update(v, m1, m22, dp[u][m1][m2] + w);
            if(!hash[v]) continue;
            for(int i = 0; i < k; i++) {
                if(hash[v] & (1 << i)) {
                    if(m22 & (1 << i)) update(v, m1 | (1 << i), m22, dp[u][m1][m2] + w + ft[i]);
                    update(v, m1 | (1 << i), m22, dp[u][m1][m2] + w + t[i]);
                }
            }
        }
    }
    int ans = inf;
    for(int i = 0; i < nn; i++) {
        ans = min(ans, dp[0][nn-1][i]);
    }
    printf("%d\n", ans);
}

int main() {
    int T, Case = 1;
    int u, v, w;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 0; i < n; i++) {
            hash[i] = 0;
            fp[i] = 0;
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                maz[i][j] = inf;
            }
            maz[i][i] = 0;
        }
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            u--, v--;
            maz[u][v] = maz[v][u] = w;
        }
        floyd();
        for(int i = 0; i < k; i++) {
            scanf("%d%d%d%d",&u, &t[i], &ft[i], &m);
            hash[u-1] |= (1 << i);
            while(m--) {
                scanf("%d", &v);
                fp[v-1] |= (1 << i);
            }
        }
        printf("Case #%d: ", Case++);
        solve();
    }
    return 0;
}
