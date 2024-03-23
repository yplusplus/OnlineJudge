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
const int N = 1111;
vector<pii> vec[N];
int cnt[N];
int dist[N];
bool visit[N];
int n, m;
bool spfa() {
    int s = 0;
    queue<int> que;
    for(int i = 0; i <= n; i++) dist[i] = inf;
    memset(cnt, 0, sizeof(cnt));
    memset(visit, false, sizeof(visit));
    dist[s] = 0;
    visit[s] = true;
    cnt[s]++;
    que.push(s);
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for(int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i].fi, w = vec[u][i].se;
            if(dist[v] > dist[u] + w) {
                //cout << u << " " << v << " " << w << endl;
                dist[v] = dist[u] + w;
                if(!visit[v]) {
                    que.push(v);
                    visit[v] = true;
                    if(++cnt[v] >= n + 2) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
int main() {
    while(cin >> n >> m) {
        for(int i = 0; i <= n + 1; i++) vec[i].clear();
        for(int i = 0; i < m; i++) {
            int l, r, a, b;
            cin >> l >> r >> a >> b;
            /*
            vec[l-1].pb(mp(r, a));
            vec[r].pb(mp(l-1, -b));
            */
            vec[r].pb(mp(l-1, -a));
            vec[l-1].pb(mp(r, b));
        }
        for(int i = 1; i <= n; i++) {
            vec[i-1].pb(mp(i, 10000));
            vec[i].pb(mp(i - 1, 10000));
        }
        if(spfa()) {
            for(int i = 1; i <= n; i++) {
                printf("%d%c", dist[i] - dist[i-1], i == n ? '\n' : ' ');
            }
        } else puts("The spacecraft is broken!");
    }
    return 0;
}
