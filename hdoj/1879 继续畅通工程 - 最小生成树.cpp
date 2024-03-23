#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 110
int fa[maxn];
int n, tot;
struct Edge {
    int u, v, w;
    Edge(){}
    Edge(int _u, int _v, int _w) {
        u = _u, v = _v, w = _w;
    }
    bool operator<(const Edge &x) const {
        return w < x.w;
    }
}et[maxn*maxn];

void init() {
    for(int i = 0; i < maxn; i++)
        fa[i] = i;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a), b = find(b);
    if(a != b) {
        fa[a] = b;
        return true;
    }
    return false;
}

int main() {
    while(~scanf("%d", &n), n) {
        init();
        int m = n * (n - 1) / 2;
        tot = 0;
        for(int i = 0; i < m; i++) {
            int u, v, w, id;
            scanf("%d%d%d%d", &u, &v, &w, &id);
            if(id) {
                Union(u, v);
            } else {
                et[tot++] = Edge(u, v, w);
            }
        }
        sort(et, et + tot);
        int ans = 0;
        for(int i = 0; i < tot; i++) {
            if(Union(et[i].u, et[i].v)) {
                ans += et[i].w;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
