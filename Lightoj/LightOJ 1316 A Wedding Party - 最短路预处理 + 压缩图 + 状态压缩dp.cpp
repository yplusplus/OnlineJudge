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
const int inf = 1 << 25;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 510
vector<int> vec;
vector<pii> g[maxn];
int hash[maxn];
bool visit[20][1<<15];
int dp[20][1<<15];
int n, m, k;
int maz[maxn][maxn];
void spfa(int s) {
    bool visit[maxn];
    int dist[maxn];
    memset(visit, false, sizeof(visit));
    for(int i = 0; i < n; i++) dist[i] = inf;
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = 0;
        for(int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].fi, w = g[u][i].se;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if(!visit[v]) {
                    que.push(v);
                    visit[v] = 1;
                }
            }
        }
    }
    for(int i = 0; i < n; i++) maz[s][i] = dist[i];
}

void solve() {
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < (1 << 15); j++)
            dp[i][j] = inf;
    memset(visit, false, sizeof(visit));
    queue<int> que;
    que.push(0), que.push(0); 
    dp[0][0] = 0;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        int m = que.front(); que.pop();
        visit[u][m] = false;
        for(int i = 0; i < vec.size(); i++) {
            int v = vec[i];
            int mm = m | hash[v];
            if(dp[i][mm] > dp[u][m] + maz[vec[u]][v]) {
                dp[i][mm] = dp[u][m] + maz[vec[u]][v];
                if(!visit[i][mm]) {
                    que.push(i), que.push(mm);
                    visit[i][mm] = true;
                }
            }
        }
    }
    int ans = inf, ans_cnt = -1;
    int t = vec.size() - 1;
    for(int i = 0; i < (1 << k); i++) {
        if(dp[t][i] >= inf) continue;
        int cnt = 0;
        for(int j = 0; j < k; j++)
            if(i & (1 << j)) cnt++;
        if(ans_cnt < cnt) {
            ans = dp[t][i], ans_cnt = cnt;
        } else if(ans_cnt == cnt && dp[t][i] < ans) ans = dp[t][i];
    }
    if(ans_cnt == -1) puts("Impossible");
    else printf("%d %d\n", ans_cnt, ans);
}

int main() {
    int T, Case = 1;
    int u, v, w, x;
    scanf("%d'", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 0; i < n; i++) g[i].clear();
        vec.clear();
        memset(hash, 0, sizeof(hash));
        for(int i = 0; i < k; i++) {
            scanf("%d", &x);
            hash[x] = 1 << i;
            vec.pb(x);
        }
        vec.pb(0), vec.pb(n - 1);
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());

        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            g[u].pb(mp(v, w));
        }
        for(int i = 0; i < vec.size(); i++) spfa(vec[i]);
        printf("Case %d: ", Case++);
        solve();
    }
    return 0;
}
