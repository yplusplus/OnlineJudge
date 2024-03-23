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
#define maxn 2550
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
int fac[20];
int r, c;
int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1, -1, 0, 1, 0};
int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2, 0, 1, 0, -1};
int g[55][55];
bool vist[maxn];
int match[maxn], n;
vector<int> vec[maxn];
bool check(int x, int y) {
    if(x > 0 && x <= r && y > 0 && y <= c && g[x][y] != -1) return true;
    return false;
}
bool dfs(int u) {
    int size = vec[u].size();
    for(int i = 0; i < size; i++) {
        int v = vec[u][i];
        if (!vist[v]) {
            vist[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int Match() {//二分图匹配
    int cnt = 0;
    memset(match, -1, sizeof (match));
    for (int u = 1; u <= n; u++) {
        memset(vist, false, sizeof (vist));
        if (dfs(u)) cnt++; //每找到一条增广路，匹配数+1
    }
    return cnt; //返回最大匹配数
}

int main() {
    fac[0] = 1;
    for(int i = 1; i < 15; i++) fac[i] = fac[i-1] * 2;
    int Case = 1;
    while(~scanf("%d%d", &r, &c)) {
        if(!r && !c) break;
        n = r * c;
        for(int i = 0; i < maxn; i++) vec[i].clear();
        for(int i = 1; i <= r; i++)
            for(int j = 1; j <= c; j++)
                scanf("%d", &g[i][j]);
        for(int i = 1; i <= r; i++) {
           for(int j = 1; j <= c; j++) {
               if(g[i][j] == -1) continue;
                for(int k = 0; k < 12; k++) {
                    if(fac[k] & g[i][j]) {
                        int x = i + dx[k], y = j + dy[k];
                        if(!check(x, y)) continue;
                        int a = (i - 1) * c + j, b = (x - 1) * c + y;
                        if((i + j) & 1) vec[a].pb(b);
                        else vec[b].pb(a);
                    }
                }
           }
        } 
        int ans = Match();
        printf("%d. %d\n", Case++, ans);
    }
    return 0;
}
