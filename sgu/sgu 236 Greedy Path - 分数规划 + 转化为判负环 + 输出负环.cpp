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
const int N = 55;
struct Edge {
    int v, c, t;
    Edge(){}
    Edge(int _v, int _c, int _t) {
        v = _v, c = _c, t = _t;
    }
};
vector<Edge> vec[N];
const double eps = 1e-6;
int n, m;
int cnt[N], pre[N];
double dist[N];
bool visit[N];
int scheme[N], tot;
//分数规划
//首先转化为判定性问题，假设存在一个环的比率大于r
//∑Cij / ∑Tij > r
//∑(r * Tij - Cij) < 0
//等价在新图(原边变成 r * Tij - Cij)存在一个负环
//然后就可以二分这个r，判新图是否存在负环
//分数规划的题目都是这样做，经典的最优比率生成树也是
//输出负环的时候，第一个出来的点不一定就在负环，虽然先遍历一次！！！
bool spfa(double r) {
    int que[N], head = 0, tail = 0;
    for(int i = 1; i <= n; i++) {
        dist[i] = 0.0;
        pre[i] = -1;
        cnt[i] = 1;
        que[tail++] = i;
        if(tail == N) tail = 0;
        visit[i] = true;
    }
    while(head != tail) {
        int u = que[head++];
        if(head == N) head = 0;
        visit[u] = false;
        for(int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i].v;
            double c = vec[u][i].c, t = vec[u][i].t;
            if(dist[u] + r * t - c + eps < dist[v]) {
                dist[v] = dist[u] + r * t - c;
                pre[v] = u;
                if(!visit[v]) {
                    que[tail++] = v;
                    if(tail == N) tail = 0;
                    visit[v] = true;
                    if(++cnt[v] == n) {
                        memset(visit, false, sizeof(visit));
                        int idx = v;
                        while(!visit[idx]) {
                            visit[idx] = true;
                            idx = pre[idx];
                        }
                        tot = 0;
                        int tmp = idx;
                        scheme[tot++] = tmp;
                        tmp = pre[tmp];
                        while(tmp != idx) {
                            scheme[tot++] = tmp;
                            tmp = pre[tmp];
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    while(cin >> n >> m) {
        for(int i = 1; i <= n; i++) vec[i].clear();
        int u, v, c, t;
        for(int i = 0; i < m; i++) {
            cin >> u >> v >> c >> t;
            vec[u].pb(Edge(v, c, t));
        }
        double l = 0.0, r = 5555;
        tot = 0;
        for(int i = 0; i < 50; i++) {
            double mid = (l + r) / 2.0;
            if(spfa(mid)) l = mid;
            else r = mid;
        }
        cout << tot << endl;
        for(int i = tot - 1; i >= 0; i--) {
            printf("%d%c", scheme[i], i == 0 ? '\n' : ' ');
        }
    }
    return 0;
}
