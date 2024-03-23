#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
using namespace std;
#define pb push_back
#define maxn 20050
vector<int> vec[maxn];
int n;
int balance[maxn], cnt[maxn];

void dfs(int u, int fa) {
    int size = vec[u].size();
    cnt[u] = 1;
    int tmp = 0;
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        if(v == fa) continue;
        dfs(v, u);
        cnt[u] += cnt[v];
        tmp = max(cnt[v], tmp);
    }
    balance[u] = max(tmp, n - cnt[u]); 
}

int main() {
    int T, u, v;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < maxn; i++) vec[i].clear();
        for(int i = 0; i < n - 1; i++) {
            scanf("%d%d", &u, &v);
            vec[u].pb(v), vec[v].pb(u);
        }
        dfs(1, -1);
        int ans = 1;
        for(int i = 1; i <= n; i++) {
            if(balance[ans] > balance[i]) ans = i;
        }
        cout << ans << " " << balance[ans] << endl;
    }
    return 0;
}
