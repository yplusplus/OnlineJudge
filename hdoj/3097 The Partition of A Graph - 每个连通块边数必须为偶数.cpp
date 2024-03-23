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

const int N = 1111;
vector<int> vec[N];
bool visit[N];
int n, m;
int counter;

void dfs(int u) {
    visit[u] = true;
    counter += vec[u].size();
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m, n + m) {
        for (int i = 1; i <= n; i++) vec[i].clear();
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            vec[a].pb(b);
            vec[b].pb(a);
        }
        bool found = m & 1;
        memset(visit, false, sizeof(visit));
        for (int i = 1; i <= n && !found; i++) {
            if (!visit[i]) {
                counter = 0;
                dfs(i);
                if (counter & 3) { found = true; }
            }
        }
        puts(found ? "No" : "Yes");
    }
    return 0;
}
