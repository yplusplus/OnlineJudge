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
const int N = 1111;
vector<int> vec[N];
int whichDay[N];
bool win[N];
int n, m;

//图上的博弈
//bfs一次把图变成DAG，然后可以求出每个点的胜负状态

void bfs(int s) {
    queue<int> que;
    memset(whichDay, -1, sizeof(whichDay)); 
    que.push(s);
    whichDay[s] = 1;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        for(int i = 0; i < vec[u].size(); i++) {
            int v = vec[u][i];
            if(whichDay[v] == -1) {
                whichDay[v] = whichDay[u] + 1;
                que.push(v);
            }
        }
    }
}

void dfs(int u) {
    win[u] = false;
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(whichDay[v] > whichDay[u]) {
            dfs(v);
            if(!win[v]) win[u] = true;
        }
    }
}

int main() {
    while(cin >> n >> m) {
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            vec[a].pb(b);
            vec[b].pb(a);
        }
        bfs(1);
        dfs(1);
        puts(win[1] ? "Vladimir" : "Nikolay");
    }
    return 0;
}
