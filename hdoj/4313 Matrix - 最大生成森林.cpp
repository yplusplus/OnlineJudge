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
#define maxn 100050
int fa[maxn], tot;
int n, k;
struct Edge {
    int u, v;
    ll w;
    Edge(){};
    Edge(int _u, int _v, ll _w) {
        u = _u, v = _v, w = _w;
    }
    bool operator<(const Edge &x) const {
        return w > x.w;
    }
}et[maxn];

void init() {
    for(int i = 0; i < maxn; i++) fa[i] = i;
}

int find(int x) {
    return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    else {
        fa[a] = b;
        return true;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        init();
        tot = 0;
        for(int i = 1; i < n; i++) {
            int u, v;
            ll w;
            scanf("%d%d%I64d", &u, &v, &w);
            et[tot++] = Edge(u, v, w);
        }
        for(int i = 0; i < k; i++) {
            int a;
            scanf("%d", &a);
            fa[a] = n;
        }
        sort(et, et + tot);
        ll ans = 0;
        for(int i = 0; i < tot; i++) {
            if(!Union(et[i].u, et[i].v)) ans += et[i].w;
        }
        cout << ans << endl;
    }
    return 0;
}
