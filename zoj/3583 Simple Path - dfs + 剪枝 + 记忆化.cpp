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
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 110
int n, m, s, t;


vector<int> vec[maxn];
int pre[maxn];
bool visit[maxn], inpath[maxn];


void dfs(int u) {
    if(inpath[u]) {
        int tmp = pre[u];
        while(tmp != s) {
            inpath[tmp] = true;
            tmp = pre[tmp];
        }
        return;
    }
    int size = vec[u].size();
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        if(!visit[v]) {
            visit[v] = true;
            pre[v] = u;
            dfs(v);
            visit[v] = false;
        }
    }
}

int main() {
    int u, v;
    while(~scanf("%d%d%d%d", &n, &m, &s, &t)) {
        for(int i = 0; i < maxn; i++) vec[i].clear();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            vec[u].pb(v);
            vec[v].pb(u);
        }
        memset(visit, false, sizeof(visit));
        memset(inpath, false, sizeof(inpath));
        memset(pre, -1, sizeof(pre));
        inpath[t] = true, visit[s] = true;
        dfs(s);
        inpath[s] = true;
        int ans = n;
        for(int i = 0; i < n; i++) {
            if(inpath[i]) {
                ans--;
//                cout << i << endl;
            }
        } 
        cout << ans << endl;
    }
    return 0;
}
