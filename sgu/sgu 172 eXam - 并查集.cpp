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
const int N = 222;
int fa[N<<1];
int n, m;
int whichDay[N];
vector<int> vec[N<<1];

//类似2-sat问题，但是由于图是严格对称且无向的，直接用并查集判断即可
//此题亦可用dfs或bfs判断原图是否为二分图
void init() {
    for(int i = 0; i < (N << 1); i++) {
        fa[i] = i;
        vec[i].clear();
    }
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void Union(int a, int b) {
    vec[a].pb(b);
    vec[b].pb(a);
    a = find(a), b = find(b);
    fa[a] = b;
}

void dfs(int u, int day) {
    int tmp = u;
    if(tmp > n) tmp -= n;
    whichDay[tmp] = day;
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        tmp = v;
        if(tmp > n) tmp -= n;
        if(whichDay[tmp] == -1) {
            dfs(v, !day);
        }
    }
}

int main() {
    while(cin >> n >> m) {
        bool found = false;
        init();
        for(int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            Union(a, b + n);
            Union(a + n, b);
        }
        for(int i = 1; i <= n; i++) {
            if(find(i) == find(i + n)) found = true;
        }

        if(found) puts("no");
        else {
            puts("yes");
            memset(whichDay, -1, sizeof(whichDay));
            for(int i = 1; i <= n; i++) {
                if(whichDay[i] == -1) dfs(i, 0);
            }
            vector<int> scheme;
            for(int i = 1; i <= n; i++) {
                if(!whichDay[i]) scheme.pb(i);
            }
            cout << scheme.size() << endl;
            for(int i = 0; i < scheme.size(); i++) {
                printf("%d%c", scheme[i], i == scheme.size() - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
