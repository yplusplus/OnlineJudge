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
#define maxn 55
#define maxm 2500
const int inf = 1 << 20;
int eh[maxn], tot;
int n, m, k;
struct Edge {
    int u, v, w, next;
}et[maxm];
int dp[maxn][1<<10];
bool visit[maxn][1<<10];
int hash[maxn];
int minn[1<<10];
void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int w) {
    Edge e = {u, v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

bool check(int mask) {//�жϺϷ�״̬
    int a = 0, b = 0;
    for(int i = 0; i < k; i++)
        if(mask & (1<<i)) a++;
    for(int i = k; i < 2 * k; i++) 
        if(mask & (1<<i)) b++;
    return a == b;
}

void solve() {

    memset(visit, false, sizeof(visit));
    int base = 10000, nn = 1<<(2*k);
    queue<int> que;

    for(int i = 0; i <= n; i++) {
        hash[i] = 0;
        for(int j = 0; j < nn; j++)
            dp[i][j] = inf;
    }

    for(int i = 1; i <= k; i++) {
        hash[i] = 1<<(i-1);
        dp[i][hash[i]] = 0;
        que.push(i * base + hash[i]);
        visit[i][hash[i]] = true;
    }
    
    for(int i = 0; i < k; i++) {
        hash[n-i] = 1<<(k+i);
        dp[n-i][hash[n-i]] = 0;
        que.push((n-i) * base + hash[n-i]);
        visit[n-i][hash[n-i]] = true;
    }

    while(!que.empty()) {
        int u = que.front();
        que.pop();
        int mask = u % base;
        u /= base;
        visit[u][mask] = false;
        for(int now = eh[u]; now != -1; now = et[now].next) {
            int v = et[now].v, w = et[now].w;
            int nmask = mask | hash[v];
            if(dp[v][nmask] > dp[u][mask] + w) {
                dp[v][nmask] = dp[u][mask] + w;
                if(!visit[v][nmask]) {
                    que.push(v * base + nmask);
                    visit[v][nmask] = true;
                }
            }
        }
        int t = nn - 1 - mask;
        for(int i = t; i; i = (i-1) & t) {
            int nmask = mask | i;
            if(dp[u][nmask] > dp[u][mask] + dp[u][i|hash[u]]) {
                dp[u][nmask] = dp[u][mask] + dp[u][i|hash[u]];
                if(!visit[u][nmask]) {
                    que.push(u * base + nmask);
                    visit[u][nmask] = true;
                }
            }
        }
    }
    
    for(int i = 0; i < nn; i++)
        minn[i] = inf;

    for(int i = 1; i <= n; i++) 
        for(int j = 0; j < nn; j++)
            minn[j] = min(minn[j], dp[i][j]);
    
    for(int i = 1; i < nn; i++)
        if(check(i))
            for(int j = i; j; j = (j-1) & i)
                if(check(j)) minn[i] = min(minn[i], minn[j] + minn[i-j]);

    int ans = minn[nn-1];
    if(ans == inf) cout << "No solution" << endl;
    else cout << ans << endl;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &k);
        init();
        for(int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        solve();
    }
    return 0;
}
