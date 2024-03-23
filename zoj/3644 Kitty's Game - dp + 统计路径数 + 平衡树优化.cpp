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
#define maxn 2010
const ll MOD = 1000000007LL;
ll p[maxn], k;
vector<int> vec[maxn];
map<int, ll> table[maxn];
int in[maxn];
int que[maxn], tot;
int n, m;
bool visit[maxn];

void spfa() {
    memset(visit, false, sizeof(visit));
    queue<int> que;
    table[1][p[1]] = 1;
    que.push(1);
    visit[1] = true;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        if(u == n) continue;
        for(map<int, ll>::iterator it = table[u].begin(); it != table[u].end(); it++) {
            for(int j = 0; j < vec[u].size(); j++) {
                int v = vec[u][j];
                ll x = it->fi;
                ll lcm = x * p[v] / __gcd(x, p[v]);
                if(lcm == x || lcm > k) continue;
                table[v][lcm] = (table[v][lcm] + it->se) % MOD;
                if(!visit[v]) {
                    que.push(v);
                    visit[v] = true;
                }
            }
        }
        table[u].clear();
    }
}

int main() {
    while(~scanf("%d%d%lld", &n, &m, &k)) {
        for(int i = 1; i <= n; i++) {
            vec[i].clear();
            table[i].clear();
            in[i] = 0;
        }
        for(int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            in[b]++;
        }
        for(int i = 1; i <= n; i++) scanf("%lld", &p[i]);
        spfa();
        printf("%lld\n", table[n][k] % MOD);
    }
    return 0;
}
