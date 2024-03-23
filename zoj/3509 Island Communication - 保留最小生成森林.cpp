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
#define maxn 550
#define maxm 50050
int n, m;
int a[maxm], b[maxm];
int d[maxn][maxn];
char c[maxm];
vector<int> vec[maxn];
int x, y, z;

bool dfs(int s, int t, int fa) {
    if(s == t) return true;
    for(vector<int>::const_iterator it = vec[s].begin(); it != vec[s].end(); it++) {
        if(*it != fa && dfs(*it, t, s)) {
            if(z > d[s][*it]) {
                x = s;
                y = *it;
                z = d[x][y];
            }
            return true;
        }
    }
    return false;
}

int main() {
    int Case = 1;
    while(cin >> n >> m) {
        for(int i = 0; i <= n; i++) {
            vec[i].clear();
            fill(d[i], d[i] + n, maxm);
        }
        for(int i = 0; i < m; i++) {
            scanf(" %c%d%d", &c[i], &a[i], &b[i]);
            if(c[i] == 'D') d[a[i]][b[i]] = d[b[i]][a[i]] = i;
        }
        if(Case > 1) puts("");
        printf("Case %d:\n", Case++);
        for(int i = 0; i < m; i++) {
            if(c[i] == 'I') {
                z = maxm;
                if(dfs(a[i], b[i], -1)) {
                    if(z < d[a[i]][b[i]]) {
                        vec[x].erase(remove(vec[x].begin(), vec[x].end(), y), vec[x].end());
                        vec[y].erase(remove(vec[y].begin(), vec[y].end(), x), vec[y].end());
                        vec[a[i]].pb(b[i]);
                        vec[b[i]].pb(a[i]);
                    }
                } else {
                    vec[a[i]].pb(b[i]);
                    vec[b[i]].pb(a[i]);
                }
            } else if(c[i] == 'D') {
                vec[a[i]].erase(remove(vec[a[i]].begin(), vec[a[i]].end(), b[i]), vec[a[i]].end());
                vec[b[i]].erase(remove(vec[b[i]].begin(), vec[b[i]].end(), a[i]), vec[b[i]].end());
            } else {
                puts(dfs(a[i], b[i], -1) ? "YES" : "NO");
            }
        }
    }
    return 0;
}
