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
#include <sstream>
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
int eh[N], tot;
int ntot, n, m;
int val[N], cnt[N], dp[N][N];
map<string, int> id;
bool isRoot[N];
struct Edge {
    int u, v, next;
}et[N << 1];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v) {
    Edge e = {u, v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

int getId(string name) {
    int res = id[name];
    if (res == 0) {
        id[name] = ++ntot;
        return ntot;
    } else return res;
}

void dfs(int u) {
    if (u) cnt[u] = 1;
    else cnt[u] = 0;
    for (int i = 0; i <= n; i++) dp[u][i] = inf;
    dp[u][0] = 0;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        dfs(v);
        cnt[u] += cnt[v];
        for (int j = n; j >= 0; j--) {
            for (int k = 0; k <= cnt[v]; k++) {
                if (j - k >= 0) dp[u][j] = min(dp[u][j], dp[u][j - k] + dp[v][k]);
            }
        }
    }
    dp[u][cnt[u]] = min(dp[u][cnt[u]], val[u]);
}

void gao() {
    val[0] = inf;
    dfs(0);
    int ans = inf;
    for (int i = m; i <= n; i++) {
        ans = min(ans, dp[0][i]);
    }
    cout << ans << endl;
}

int main() {
    char s[111];
    while (scanf("%s", s)) {
        if (s[0] == '#') break;
        sscanf(s, "%d", &n);
        scanf("%d", &m);
        string name, line;
        init();
        ntot = 0;
        id.clear();
        memset(isRoot, true, sizeof(isRoot));
        for (int i = 1; i <= n; i++) {
            cin >> name;
            int u = getId(name);
            scanf("%d", &val[u]);
            getline(cin, line);
            istringstream stream(line);
            while (stream >> name) {
                int v = getId(name);
                addedge(u, v);
                isRoot[v] = false;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (isRoot[i]) addedge(0, i);
        }
        gao();
    }
    return 0;
}
