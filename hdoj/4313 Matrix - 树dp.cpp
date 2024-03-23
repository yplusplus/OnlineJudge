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
#define maxn 100050
const ll linf = 1LL << 50;
int eh[maxn], tot;
struct Edge {
    int v;
    ll w;
    int next;
    Edge(){}
    Edge(int _v, ll _w, int _next) {
        v = _v, w = _w, next = _next;
    }
}et[2 * maxn];
int n, k;

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v, ll w) {
    Edge e;
    e.v = v, e.w = w, e.next = eh[u];
    et[tot] = e;
    eh[u] = tot++;
}

ll dp[maxn];
bool bomb[maxn];
bool have[maxn];
ll ans;
void dfs(int u, int fa) {
    ll sum = 0;
    ll tmp = 0;
    dp[u] = linf;
    if(!have[u]) {
        return;
    }
    if(bomb[u]) {
        for(int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            ll w = et[i].w;
            if(v == fa) continue;
            dfs(v, u);
            if(have[v]) ans += min(dp[v], w);
        }
    } else {
        for(int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v;
            ll w = et[i].w;
            if(v == fa) continue;
            dfs(v, u);
            if(have[v]) sum += min(dp[v], w), tmp = max(tmp, min(dp[v], w));
        }
        ans += sum - tmp;
        dp[u] = tmp;
    }
}

void dfs1(int u, int fa) {
    if(bomb[u]) have[u] = 1;
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if(v == fa) continue;
        dfs1(v, u);
        have[u] |= have[v];
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        init();
        memset(bomb, 0, sizeof(bomb));
        memset(have, 0, sizeof(have));
        for(int i = 1; i < n; i++) {
            int a, b;
            ll c;
            scanf("%d%d%I64d", &a, &b, &c);
            addedge(a, b, c);
            addedge(b, a, c);
        }
        for(int i = 0; i < k; i++) {
            int a;
            scanf("%d", &a);
            bomb[a] = 1;
        }
        dfs1(0, -1);
        ans = 0;
        dfs(0, -1);
        printf("%I64d\n", ans);
    }
    return 0;
}
