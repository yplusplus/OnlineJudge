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

const int N = 111111;
int n, d;
int dist[N];
vector<int> vec[N];
int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> d;
        for (int i = 0; i < n; i++) vec[i].clear();
        for (int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            vec[a].pb(b);
            vec[b].pb(a);
        }
        memset(dist, -1, sizeof(dist));
        queue<int> que;
        que.push(0);
        dist[0] = 0;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i = 0; i < vec[u].size(); i++) {
                int v = vec[u][i];
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    que.push(v);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) ans += dist[i] > d;
        cout << ans << endl;
    }
    return 0;
}
