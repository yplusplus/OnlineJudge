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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 222;
int dist[N][4];
vector<pii> vec[N];
int n, m;
void bfs(int s) {
    memset(dist, -1, sizeof(dist));
    queue<int> que;
    que.push(s);
    que.push(0);
    dist[s][0] = 0;
    int u, curColor;
    while(!que.empty()) {
        u = que.front(); que.pop();
        curColor = que.front(); que.pop();
        for(int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i].fi, nextColor = vec[u][i].se;
            if(nextColor != curColor && dist[v][nextColor] == -1) {
                dist[v][nextColor] = dist[u][curColor] + 1;
                que.push(v);
                que.push(nextColor);
            }
        }
    }

}

int main() {
    while(cin >> n >> m) {
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            vec[a].pb(mp(b, c));
        }
        bfs(1);
        int ans = inf;
        for(int i = 1; i <= 3; i++) {
            if(dist[n][i] == -1) continue;
            ans = min(ans, dist[n][i]);
        }
        if(ans == inf) ans = -1;
        cout << ans << endl;
    }
    return 0;
}
