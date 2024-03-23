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

const int N = 333333;
vector<pii> vec[N];
int dist[N];
bool visit[N];
int n, m, c;
void spfa() {
    for (int i = 1; i <= 3 * n; i++) dist[i] = 1 << 30;
    dist[1] = 0;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i].fi, w = vec[u][i].se;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!visit[v]) {
                    que.push(v);
                    visit[v] = true;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m >> c;
        for (int i = 1; i <= n * 3; i++) vec[i].clear();
        for (int i = 1; i <= n; i++) {
            int level;
            cin >> level;
            if (level > 1) {
                vec[n + level].pb(mp(i, c));
                vec[i].pb(mp(n + n + level, c));
            }
            if (level < n) {
                vec[i].pb(mp(n + level + 1, c));
                vec[n + n + level + 1].pb(mp(i, c));
            }
        }
        for (int i = 0; i < m; i++) {
            int a, b, d;
            cin >> a >> b >> d;
            vec[a].pb(mp(b, d << 1));
            vec[b].pb(mp(a, d << 1));
        }
        spfa();
        int ans = dist[n];
        if (ans == 1LL << 30) ans = -1;
        else ans >>= 1;
        cout << "Case #" << Case++ << ": " << ans << endl;
    }
    return 0;
}
