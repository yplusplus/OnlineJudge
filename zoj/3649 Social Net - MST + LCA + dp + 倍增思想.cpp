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
const int inf = 1 << 28;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 33333
int angry[maxn], fa[maxn];
vector<int> vec[maxn];
int n, m, q;
int F[maxn<<1], B[maxn<<1], pos[maxn];
int rmq[maxn<<1][16], rn;
int maxValue[maxn][16], minValue[maxn][16], maxGain[maxn][16], minGain[maxn][16];
int father[maxn][16];
struct Edge {
    int a, b, c;
    Edge(){}
    Edge(int _a, int _b, int _c) {
        a = _a, b = _b, c = _c;
    }
    bool operator<(const Edge &x) const {
        return c > x.c;
    }
}et[55555];

int find(int x) {
    return (x == fa[x]) ? fa[x] : (fa[x] = find(fa[x]));
}

bool Union(int a, int b) {
    a = find(fa[a]), b = find(fa[b]);
    if(a == b) return false;
    fa[a] = b;
    return true;
}

ll getMST() {
    ll res = 0;
    sort(et, et + m);
    for(int i = 0; i < m; i++) {
        int a = et[i].a, b = et[i].b, c = et[i].c;
        if(Union(a, b)) {
            res += c;
            vec[a].pb(b);
            vec[b].pb(a);
        }
    }
    return res;
}

void dfs(int u, int pre, int deep) {
    F[++rn] = u, B[rn] = deep, pos[u] = rn;
    for(int i = 1; i < 16; i++) {
        if(father[u][i-1] != -1) {
            int rec = father[u][i-1];
            father[u][i] = father[rec][i-1];
            if(father[u][i] == -1) continue;
            maxValue[u][i] = max(maxValue[u][i-1], maxValue[rec][i-1]);
            minValue[u][i] = min(minValue[u][i-1], minValue[rec][i-1]);
            maxGain[u][i] = max(maxValue[rec][i-1] - minValue[u][i-1], max(maxGain[u][i-1], maxGain[rec][i-1]));
            minGain[u][i] = min(minValue[rec][i-1] - maxValue[u][i-1], min(minGain[u][i-1], minGain[rec][i-1]));
        }
    }
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(v == pre) continue;
        father[v][0] = u;
        maxValue[v][0] = max(angry[v], angry[u]);
        minValue[v][0] = min(angry[v], angry[u]);
        if(angry[v] < angry[u]) {
            maxGain[v][0] = angry[u] - angry[v];
            minGain[v][0] = 0; 
        } else {
            maxGain[v][0] = 0;
            minGain[v][0] = angry[u] - angry[v];
        }
        dfs(v, u, deep + 1);
        F[++rn] = u, B[rn] = deep;
    }
}

void Init_RMQ() {
    for(int i = 1; i <= rn; i++) rmq[i][0] = i;
    for(int j = 1; (1<<j) <= rn; j++) {
        for(int i = 1; i + (1<<j) - 1 <= rn; i++) {
            int a = rmq[i][j-1], b = rmq[i+(1<<(j-1))][j-1];
            if(B[a] < B[b]) rmq[i][j] = a;
            else rmq[i][j] = b;
        }
    }
}
int RMQ(int a, int b) {
    int k = int(log(1.0 + b - a) / log(2.0));
    int u = rmq[a][k], v = rmq[b-(1<<k)+1][k];
    if(B[u] < B[v]) return F[u];
    else return F[v];
}
int LCA(int a, int b) {
    a = pos[a], b = pos[b];
    if(a > b) return RMQ(b, a);
    else return RMQ(a, b);
}
int calc(int a, int anc, int &maxV, int &minV, int &maxG, int &minG) {
    int delta = B[pos[a]] - B[pos[anc]];
    maxV = maxG = 0, minV = minG = inf;
    for(int i = 16; i >= 0; i--) {
        if(delta & (1 << i)) {
            maxG = max(maxG, max(maxValue[a][i] - minV, maxGain[a][i]));
            minG = min(minG, min(minValue[a][i] - maxV, minGain[a][i]));
            maxV = max(maxV, maxValue[a][i]);
            minV = min(minV, minValue[a][i]);
            a = father[a][i];
        }
    }
}

int main() {
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; i++) {
            scanf("%d", &angry[i]);
            vec[i].clear();
            fa[i] = i;
        }
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            et[i] = Edge(a, b, c);
        }
        ll ans = getMST();
        cout << ans << endl;
        memset(father, -1, sizeof(father));
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < 16; j++) {
                maxValue[i][j] = 0, minValue[i][j] = inf;
                maxGain[i][j] = 0, minGain[i][j] = inf;
            }
        }

        rn = 0;
        dfs(1, 0, 0);
        Init_RMQ();
        scanf("%d", &q);
        while(q--) {
            int a, b;
            scanf("%d%d", &a, &b);
            int anc = LCA(a, b);
            int maxV[2], minV[2], maxG[2], minG[2];
            calc(a, anc, maxV[0], minV[0], maxG[0], minG[0]);
            calc(b, anc, maxV[1], minV[1], maxG[1], minG[1]);
            int ans = max(maxV[1] - minV[0], max(maxG[0], (-1) * minG[1]));
            if(ans < 0) ans = 0;
            printf("%d\n", ans);
        }
    }
    return 0;
}
