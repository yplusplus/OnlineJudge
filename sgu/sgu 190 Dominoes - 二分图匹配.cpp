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
const int N = 44;
bool maz[N][N];
vector<int> vec[N*N];
int xmatch[N*N], ymatch[N*N];
bool visit[N*N];
int n, p;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool check(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int id(int x, int y) {
    return (x - 1) * n + y;
}

bool dfs(int u) {
    for(int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if(!visit[v]) {
            visit[v] = true;
            if(ymatch[v] == -1 || dfs(ymatch[v])) {
                ymatch[v] = u;
                xmatch[u] = v;
                return true;
            }
        }
    }
    return false;
}

int Match() {
    int result = 0;
    memset(xmatch, -1, sizeof(xmatch));
    memset(ymatch, -1, sizeof(ymatch));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int u = id(i, j);
            if(vec[u].size() == 0) continue;
            memset(visit, false, sizeof(visit));
            if(dfs(u)) result++;
        }
    }
    return result;
}

void build() {
    for(int i = 1; i <= n * n; i++)  vec[i].clear();
    for(int x = 1; x <= n; x++) {
        for(int y = 1; y <= n; y++) {
            if(((x + y) % 2 == 0) && maz[x][y]) {
                for(int k = 0; k < 4; k++) {
                    int xx = x + dx[k], yy = y + dy[k];
                    if(check(xx, yy) && maz[xx][yy]) {
                        vec[id(x, y)].pb(id(xx, yy));
                    }
                }
            }
        }
    }
}

int main() {
    while(cin >> n >> p) {
        memset(maz, true, sizeof(maz));
        for(int i = 0; i < p; i++) {
            int a, b;
            cin >> a >> b;
            maz[a][b] = false;
        }
        build();
        int cnt = Match();
        if(cnt * 2 == n * n - p) {
            puts("Yes");
            vector<pii> horizon, vertical;
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    if((i + j) % 2 == 0 && maz[i][j]) {
                        int u = id(i, j);
                        int v = xmatch[u];
                        int ii = v / n + 1, jj = v % n;
                        if(jj == 0) jj = n, ii--;
                        if(i == ii) {
                            vertical.pb(mp(i, min(j, jj)));
                        } else {
                            horizon.pb(mp(min(i, ii), j));
                        }
                    }
                }
            }
            cout << horizon.size() << endl;
            for(int i = 0; i < horizon.size(); i++) {
                cout << horizon[i].fi << " " << horizon[i].se << endl;
            }
            cout << vertical.size() << endl;
            for(int i = 0; i < vertical.size(); i++) {
                cout << vertical[i].fi << " " << vertical[i].se << endl;
            }
        } else puts("No");
    }
    return 0;
}
