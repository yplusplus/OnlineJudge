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
#define maxn 30
bool maz[maxn][maxn], visit[maxn];
int color[maxn];
int n;
char a, ch;

int dfs(int u, int cnt) {
    memset(visit, false, sizeof(visit));
    if(u == n) return true;
    for(int i = 0; i < n; i++) {
        if(color[i] != -1 && maz[u][i]) {
            visit[color[i]] = true;
        }
    }
    for(int i = 0; i < cnt; i++) {
        if(!visit[i]) {
            color[u] = i;
            if(dfs(u+1, cnt)) return true;
        }
    }
    return false;
}

void solve() {
    int ans = 5;
    for(int i = 1; i < 5; i++) {
        memset(color, -1, sizeof(color));
        if(dfs(0, i)) {
            ans = i;
            break;
        }
    }
    if(ans == 1) printf("1 channel needed.\n");
    else printf("%d channels needed.\n", ans);
}

int main() {
    while(~scanf("%d", &n), n) {
        getchar();
        memset(maz, false, sizeof(maz));
        for(int i = 0; i < n; i++) {
            scanf("%c:", &a);
            while((ch = getchar()) != 10) {
                maz[a-'A'][ch-'A'] = maz[ch-'A'][a-'A'] = true;
            }
        }
        solve();
    }
    return 0;
}
