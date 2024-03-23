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
#define maxn 310
int c[maxn][maxn];
bool visit[maxn];
int dist[maxn];
int n;
void spfa(int s, int &cir) {
    memset(visit, false, sizeof(visit));
    for(int i = 1; i <= n; i++) dist[i] = inf;
    dist[s] = 0;
    cir = inf;
    queue<int> que;
    que.push(s);
    visit[s] = 1;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = 0;
        for(int i = 1; i <= n; i++) {
            if(i == s && u != s) cir = min(cir, dist[u] + c[u][i]);
            if(dist[i] > dist[u] + c[u][i]) {
                dist[i] = dist[u] + c[u][i];
                if(!visit[i]) {
                    que.push(i);
                    visit[i] = 1;
                }
            }
        }
    }
}

int main() {
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                scanf("%d", &c[i][j]);
        int c1, c2;
        spfa(1, c1);
        int ans = dist[n];
        spfa(n, c2);
        ans = min(ans, c1 + c2);
        printf("%d\n", ans);
    }
    return 0;
}
