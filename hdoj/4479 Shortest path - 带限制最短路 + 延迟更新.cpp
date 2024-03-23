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

const int N = 11111;
const int M = 55555;
int n, m;
struct Edge {
    int u, v, w;
    void read() {
        scanf("%d%d%d", &u, &v, &w);
    }
    bool operator<(const Edge &x) const {
        return w < x.w;
    }
} et[M];

ll dist[N], temp_dist[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            et[i].read();
        }
        sort(et, et + m);
        for (int i = 1; i <= n; i++) dist[i] = linf, temp_dist[i] = linf;
        dist[1] = 0;
        set<int> node_set;
        for (int i = 0; i < m; ) {
            int now = et[i].w;
            node_set.clear();
            while (i < m && et[i].w == now) {
                int u = et[i].u, v = et[i].v;
                if (dist[u] > dist[v] + now) {
                    temp_dist[u] = min(temp_dist[u], dist[v] + now);
                    node_set.insert(u);
                }
                if (dist[v] > dist[u] + now) {
                    temp_dist[v] = min(temp_dist[v], dist[u] + now);
                    node_set.insert(v);
                }
                i++;
            }
            for (set<int>::iterator it = node_set.begin(); it != node_set.end(); it++) {
                dist[*it] = temp_dist[*it];
                temp_dist[*it] = linf;
            }
        }
        ll ans = dist[n];
        if (ans == linf) puts("No answer");
        else cout << ans << endl;
    }
    return 0;
}
