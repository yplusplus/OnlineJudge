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

const int N = 111111;
const int M = N;

pair<int, pii> edge[M];
int n, m;
int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    fa[a] = b;
    return true;
}

int solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) fa[i] = i;
    sort(edge, edge + m);
    for (int i = 0, j; i < m; i = j + 1) {
        j = i;
        while (j + 1 < m && edge[j].fi == edge[j + 1].fi) j++;
        for (int k = i; k <= j; k++) {
            if (find(edge[k].se.fi) != find(edge[k].se.se)) ans++;
        }
        for (int k = i; k <= j; k++) {
            Union(edge[k].se.fi, edge[k].se.se);
        }
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            edge[i] = mp(c, mp(a, b));
        }
        printf("%d\n", solve());
    }
    return 0;
}
