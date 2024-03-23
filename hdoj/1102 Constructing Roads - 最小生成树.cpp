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
#define maxn 110
int n, m;
int fa[maxn];
int maz[maxn][maxn];
struct Edge {
    int u, v, w;
    Edge(int _u, int _v, int _w) {
        u = _u, v = _v, w = _w;
    }
    bool operator<(const Edge &x) const {
        return w < x.w;
    }
};
vector<Edge> vec;
void init() {
    for(int i = 0; i < maxn; i++) fa[i] = i;
}

int find(int x) {
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(fa[a]), b = find(fa[b]);
    if(a == b) return false;
    fa[a] = b;
    return true;
}

int solve() {
    int cost = 0;
    for(int i = 0; i < vec.size(); i++) {
        int a = vec[i].u, b = vec[i].v, c = vec[i].w;
        if(Union(a, b)) cost += c;
    }
    return cost;
} 

int main() {
    int a, b, c;
    while(~scanf("%d", &n)) {
        vec.clear();
        init();
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &c);
                vec.pb(Edge(i, j, c));
            }
        }
        sort(vec.begin(), vec.end());
        scanf("%d", &m);
        while(m--) {
            scanf("%d%d", &a, &b);
            Union(a, b);
        }
        printf("%d\n", solve());
    }
    return 0;
}
