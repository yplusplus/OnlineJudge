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

const int N = 1111;
vector<int> g[N];
int rank[N], type[N];
char name[N][25];
int match[N];
bool visit[N];
int n;
int get_type(char ch) {
    if (ch == 'a') return 0;
    else if (ch == 's') return 1;
    else return 2;
}

bool dfs(int u) {
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!visit[v]) {
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
    int res = 0;
    memset(match, -1, sizeof(match));
    for (int i = 1; i <= n; i++) {
        if (rank[i] % 4 < 2) {
            memset(visit, false, sizeof(visit));
            res += dfs(i);
        }
    }
    return res;
}

int main() {
    while (~scanf("%d", &n)) {
        char str[15];
        for (int i = 1; i <= n; i++) {
            scanf("%s%s%d", name[i], str, &rank[i]);
            type[i] = get_type(str[0]);
        }
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1; i <= n; i++) {
            if (rank[i] % 4 < 2) {
                for (int j = 1; j <= n; j++) {
                    if (abs(rank[i] - rank[j]) == 2) {
                        if (type[i] == 0 || type[j] == 0 || type[i] + type[j] == 3) g[i].pb(j);
                    }
                }
            }
        }
        int ans = Match();
        printf("%d\n", ans);
        for (int i = 1; i <= n; i++) {
            if (match[i] != -1) {
                int a = i, b = match[i];
                if (type[a] == 2 || type[b] == 1) swap(a, b);
                printf("%s %s\n", name[a], name[b]);
            }
        }
    }

    return 0;
}
