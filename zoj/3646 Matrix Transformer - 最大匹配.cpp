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
#define maxn 250
int n;
char board[maxn][maxn];
bool maz[maxn][maxn];
bool visit[maxn];
int match[maxn];

bool dfs(int u) {
    for(int v = 0; v < n; v++) {
        if(maz[u][v] && !visit[v]) {
            visit[v] = true;
            if(match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int Match() {
    int cnt = 0;
    memset(match, -1, sizeof(match));
    for(int u = 0; u < n; u++) {
        memset(visit, false, sizeof(visit));
        if(dfs(u)) cnt++;
    }
    return cnt;
}

int main() {
    while(~scanf("%d", &n)) {
        for(int i = 0; i < n; i++) scanf("%s", board[i]);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                maz[i][j] = board[i][j] == 'U';
            }
        }
        if(Match() == n) puts("YES");
        else puts("NO");
    }
    return 0;
}
