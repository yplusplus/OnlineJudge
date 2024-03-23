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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 111;
bool maz[N][N];
vector<int> vec[N];
int n;
bool check(int a, int b) {
    return !(maz[a][b] && maz[b][a]);
}

bool found;
int visit[N];
void dfs(int u, int fa, int dep) {
    visit[u] = dep;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa) continue;
        if (visit[v] != -1) {
            if (visit[u] == visit[v]) found = true;
        } else {
            dfs(v, u, dep ^ 1);
        }
    }
}

int main() {
    while (~scanf("%d", &n)) {
        memset(maz, false, sizeof(maz));
        for (int i = 1; i <= n; i++) {
            vec[i].clear();
            int k;
            while (scanf("%d", &k), k) {
                maz[i][k] = true;
            }
            for (int j = 1; j < i; j++) {
                if (check(i, j)) vec[i].pb(j), vec[j].pb(i);
            }
        }
        memset(visit, -1, sizeof(visit));
        found = false;
        for (int i = 1; i <= n; i++) {
            if (visit[i] == -1) dfs(i, 0, 0);
        }
        puts(found ? "NO" : "YES");
    }
    return 0;
}
