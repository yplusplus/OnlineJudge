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
const int N = 111;
int n, m;
int ti[N][N];
int limit, id;
bool visit[N];
int match[N];
bool dfs(int u) {
    for (int v = 0; v < n; v++) {
        if (ti[u][v] < limit && !visit[v] && v != id) {
            visit[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int Match() {
    int result = 0;
    memset(match, -1, sizeof(match));
    for (int u = 0; u < n; u++) {
        if (u == m) continue;
        memset(visit, false, sizeof(visit));
        if (dfs(u)) result++;
    }
    return result;
}

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> ti[i][j];
            }
        }
        cin >> m;
        m--;
        vector<int> scheme;
        for (int i = 0; i < n; i++) {
            limit = ti[m][i];
            id = i;
            if (Match() == n - 1) scheme.pb(i);
        }
        if (scheme.size() == 0) puts("-1");
        else {
            for (int i = 0; i < scheme.size(); i++) {
                printf("%d%c", scheme[i] + 1, i == scheme.size() - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
