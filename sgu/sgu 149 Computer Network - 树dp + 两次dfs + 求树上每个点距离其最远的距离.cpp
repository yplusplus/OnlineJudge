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
vector<pii> vec[N];
ll down[N], up[N];
int son[N][2];
ll edge[N][2];
int n;

//增加一个虚拟点0，方便实现
inline ll max(ll a, ll b) {
    return a > b ? a : b;
}

void dfsForDown(int u) {
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].fi, w = vec[u][i].se;
        dfsForDown(v);
        down[u] = max(down[u], down[v] + w);
        if(down[son[u][0]] + edge[u][0] <= down[v] + w) {
            son[u][1] = son[u][0];
            edge[u][1] = edge[u][0];
            son[u][0] = v;
            edge[u][0] = w;
        } else if(down[son[u][1]] + edge[u][1] <= down[v] + w) {
            son[u][1] = v;
            edge[u][1] = w;
        }
    }
}

void dfsForUp(int u, int fa, ll t) {
    if(fa) {
        if(son[fa][0] == u) {
            up[u] = t + max(down[son[fa][1]] + edge[fa][1], up[fa]);
        } else {
            up[u] = t + max(down[son[fa][0]] + edge[fa][0], up[fa]);
        }
    }
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i].fi, w = vec[u][i].se;
        dfsForUp(v, u, w);
    }
}

int main() {
    while(cin >> n) {
        int father, w;
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 2; i <= n; i++) {
            cin >> father >> w;
            vec[father].pb(mp(i, w));
        }
        memset(down, 0, sizeof(down));
        memset(up, 0, sizeof(up));
        memset(son, 0, sizeof(son)); 
        memset(edge, -1, sizeof(edge)); 
        dfsForDown(1);
        dfsForUp(1, 0, 0);
        for(int i = 1; i <= n; i++) {
            //cout << "**********" << endl;
            //cout << i << " " << up[i] << " " << down[i] << endl;
            //cout << son[i][0] << " " << edge[i][0] << endl;
            //cout << son[i][1] << " " << edge[i][1] << endl;
            cout << max(down[i], up[i]) << endl;
        }
    }
    return 0;
}
