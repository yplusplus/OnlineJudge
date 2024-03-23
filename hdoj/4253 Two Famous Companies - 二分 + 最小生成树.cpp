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
struct Edge {
    int u, v, w, id;
    Edge(){}
    Edge(int _u, int _v, int _w, int _id) {
        u = _u, v = _v, w = _w, id = _id;
    }
    bool operator<(const Edge &x) const {
        if(w != x.w) return w < x.w;
        else return id < x.id;
    }
}et[2][100050], e;
int tot, tot1;
int n, m, k, cost;
int fa[50050];

int find(int x) {
    return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}

bool merge(int u, int v) {
    u = find(fa[u]), v = find(fa[v]);
    if(u != v) {
        fa[u] = v;
        return true;
    } else return false;
}

bool check(int w) {
    cost = 0;
    int cnt = 0;
    for(int i = 0; i < n; i++) fa[i] = i;
    int i = 0, j = 0;
    while(i < tot || j < tot1) {
        if(et[0][i].w + w <= et[1][j].w) {
            e = et[0][i++];
            e.w += w;
        } else e = et[1][j++];
        if(merge(e.u, e.v)) {
            if(!e.id) cnt++;
            cost += e.w;
        }
    }
    return cnt >= k;
}

int main() {
    int Case = 1;
    while(~scanf("%d%d%d", &n, &m, &k)) {
        tot = tot1 = 0;
        for(int i = 0; i < m; i++) {
            int u, v, w, id;
            scanf("%d%d%d%d", &u, &v, &w, &id);
            if(id) et[1][tot1++] = Edge(u, v, w, id);
            else et[0][tot++] = Edge(u, v, w, id);
        }
        sort(et[0], et[0] + tot);
        sort(et[1], et[1] + tot1);
        et[0][tot].w = et[1][tot1].w = 1 << 30;
        int l = -100, r = 100;
        int w;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(check(mid)) w = mid, l = mid + 1;
            else r = mid - 1;
        }
        check(w);
        printf("Case %d: %d\n", Case++, cost - w * k); 
    }
    return 0;
}
