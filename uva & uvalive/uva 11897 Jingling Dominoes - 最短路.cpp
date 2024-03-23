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

#define maxn 1010
int n, m, s;
ll a[maxn][maxn], b[maxn][maxn];
ll dist[maxn];
bool visit[maxn];

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll max(ll a, ll b) {
    return a < b ? b : a;
}
void dij(int s) {
    for(int i = 0; i < n; i++) dist[i] = linf;
    dist[s] = 0;
    memset(visit, false, sizeof(visit));
    while(1) {
        int u = -1;
        for(int i = 0; i < n; i++) {
            if(!visit[i] && (u == -1 || dist[u] > dist[i])) u = i;
        }
        if(u == -1) break;
        visit[u] = true;
        for(int i = 0; i < n; i++) {
            if(!visit[i] && a[u][i] != linf && dist[i] > dist[u] + a[u][i])
                dist[i] = dist[u] + a[u][i];
        }
    }
}

bool solve(double &ans) {
    dij(s);
    ans = 0.0;
    for(int i = 0; i < n; i++) 
        if(dist[i] == linf) return false;
        else ans = max(ans, 1.0 * dist[i]);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int delta = abs(dist[i] - dist[j]);
            if(b[i][j] == 0) continue;
            if(delta == b[i][j]) continue;
            ans = max(ans, (b[i][j] - delta) / 2.0 + max(dist[i], dist[j])); 
        }
    }
    return true;
}

int main() 
{
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &s);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                a[i][j] = linf;
                b[i][j] = 0;
            }
        }
        int u, v;
        ll t;
        for(int i = 0; i < m; i++) {
            scanf("%d%d%lld", &u, &v, &t);
            a[u][v] = min(a[u][v], t);
            b[u][v] = max(b[u][v], t);
            a[v][u] = a[u][v], b[v][u] = b[u][v];
        }
        double ans;
        if(solve(ans)) printf("%.2f\n", ans);
        else puts("Sorry Amoo, your domino does not complete!");
    }
    return 0;
}
