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
const int N = 222222;
int n;
int fa[N];
ll dp[N], cnt[N];
struct Edge {
    int u, v, w;
    Edge(){}
    Edge(int _u, int _v, int _w) {
        u = _u, v = _v, w = _w;
    }
    bool operator<(const Edge &x) const {
        return w > x.w;
    }
}et[N];

void init(int n) {
    for(int i = 0; i <= n; i++) {
        fa[i] = i, dp[i] = 0, cnt[i] = 1;
    }
}

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main() {
    while(cin >> n) {
        for(int i = 0; i < n - 1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            et[i] = Edge(u, v, w);
        }
        init(n);
        sort(et, et + n - 1);
        for(int i = 0; i < n - 1; i++) {
            int a = et[i].u, b = et[i].v, c = et[i].w;
            a = find(a), b = find(b);
            dp[a] += cnt[b] * c;
            dp[b] += cnt[a] * c;
            fa[a] = b;
            cnt[b] += cnt[a];
            if(dp[a] > dp[b]) dp[b] = dp[a];
        }
        cout << dp[find(1)] << endl;
    }
    return 0;
}
