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
#define maxn 110
int n, A, B, C;
bool visit[maxn];
vector<int> vec[maxn];
int pre[maxn];
double dp[maxn];
void dfs(int u, int fa) {
    pre[u] = fa;
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dfs(v, u);
    }
}

int main() {
     while(~scanf("%d", &n)) {
        scanf("%d%d%d", &A, &B, &C);
        for(int i = 1; i <= n; i++) {
            vec[i].clear();
        }
        int u, v;
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v);
            vec[u].pb(v);
            vec[v].pb(u);
        }
        dfs(B, -1);
        memset(visit, false, sizeof(visit));
        memset(dp, 0, sizeof(dp));
        int x = C, num = 0;

        while(x != -1) {
            visit[x] = true;
            x = pre[x];
            num++;
        }
        num--;
        x = C;
        while(x != B) {
            dp[x[pre]] = dp[x] + 1.0 / num;
            x = x[pre];
        }
        x = A;
        while(!visit[x]) {
            x = pre[x];
        }
        printf("%.6f\n", dp[x]);
     }
    return 0;
}
