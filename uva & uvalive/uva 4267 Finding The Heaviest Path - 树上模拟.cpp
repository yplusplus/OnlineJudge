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
#define maxn 10050
int dp[maxn];
int val[maxn];
int root, n;
vector<int> vec[maxn];

void dfs(int u) {
    dp[u] = val[u];
    int size = vec[u].size();
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        dfs(v);
        dp[u] += dp[v];
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &root);
        for(int i = 0; i < n; i++) vec[i].clear();
        for(int i = 0; i < n; i++) {
            int cnt, v;
            scanf("%d%d", &val[i], &cnt);
            while(cnt--) {
                scanf("%d", &v);
                vec[i].pb(v);
            }
        }
        memset(dp, 0, sizeof(dp));
        dfs(root);
        int x = root;
        int ans[maxn], tot = 0, w = 0;
        ans[tot++] = x;
        w += val[x];
        int size;
        while(size = vec[x].size()) {
            int u = -1, tmp = 0;
            for(int i = 0; i < size; i++) {
                int v = vec[x][i];
                if(tmp < dp[v] || (tmp == dp[v] && v > u)) tmp = dp[v], u = v;
            }
            ans[tot++] = u;
            w += val[u];
            x = u;
        }
        cout << w << endl;
        int cnt = 0;
        for(int i = 0; i < tot; i++) {
            if(cnt) printf(" ");
            printf("%d", ans[i]);
            cnt++;
            if(cnt == 10) {
                printf("\n");
                cnt = 0;
            }
        }
        if(cnt) printf("\n");
    }
    return 0;
}
