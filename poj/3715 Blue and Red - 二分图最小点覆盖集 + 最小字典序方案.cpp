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
#define maxn 220
vector<int> vec[maxn];
int group[maxn];
int match[maxn];
bool isDeleted[maxn];
bool visit[maxn];
int n, m;
bool dfs(int u) {
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(visit[v] || isDeleted[v]) continue;
        visit[v] = true;
        if(match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int Match() {
    int cnt = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < n; i++) {
        memset(visit, false, sizeof(visit));
        if(!isDeleted[i] && dfs(i)) cnt++;
    }
    return cnt;
}

void solve() {
    memset(isDeleted, false, sizeof(isDeleted));
    vector<int> scheme;
    int res = Match();
    for(int i = 0; i < n; i++) {
        isDeleted[i] = true;
        int tmp = Match();
        if(tmp < res) res = tmp, scheme.pb(i);
        else isDeleted[i] = false;
    }
    cout << scheme.size();
    for(int i = 0; i < scheme.size(); i++)
        printf(" %d", scheme[i]);
    cout << endl;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) {
            scanf("%d", &group[i]);
            vec[i].clear();
        }
        for(int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            if(group[a] == group[b]) continue;
            vec[a].pb(b);
            vec[b].pb(a);
        }
        solve();
    }
    return 0;
}
