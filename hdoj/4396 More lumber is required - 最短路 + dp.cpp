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
#define maxn 5050
#define maxm 300050
int dp[maxn][55];
int eh[maxn], tot;
bool visit[55];
int n, m, k;
int s, t;
struct Edge {
    int v, w, next;
}et[maxm];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int w) {
    Edge e = {v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void spfa() {
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= 50; j++)
            dp[i][j] = inf;
    queue<int> que;
    que.push(0);
    visit[0] = true;
    dp[s][0] = 0;
    while(!que.empty()) {
        int m = que.front();
        que.pop();
        visit[m] = false;
        for(int u = 1; u <= n; u++) {
            if(dp[u][m] >= inf) continue;
            for(int i = eh[u]; i != -1; i = et[i].next) {
                int v = et[i].v, w = et[i].w;
                int mm = m + 1;
                if(mm > k) mm = k;
                if(dp[v][mm] > dp[u][m] + w) {
                    dp[v][mm] = dp[u][m] + w;
                    if(!visit[mm]) {
                        que.push(mm);
                        visit[mm] = true;
                    }
                }
            }
        }
    }
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        init();
        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            addedge(a, b, c);
            addedge(b, a, c);
        }
        scanf("%d%d%d", &s, &t, &k);
        k = (k + 9) / 10;
        spfa();
        if(dp[t][k] == inf) puts("-1");
        else printf("%d\n", dp[t][k]);
    }
    return 0;
}
