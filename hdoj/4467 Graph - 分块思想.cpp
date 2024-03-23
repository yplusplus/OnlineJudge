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
#include <assert.h>
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
int color[N], deg[N];
int id[N], tot;
pair<int, pair<int, ll> > edge[N];
ll w[777][777];
ll rec[777][2];
ll ans[3];
vector<pair<int, ll> > vec[N];
int n, m;

void init() {
    int limit = (int) sqrt(1.0 * m);
    tot = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] > limit) id[i] = ++tot;
        else vec[i].clear(), id[i] = 0;
        //cout << i << " " << id[i] << endl;
    }

    assert(tot <= n);

    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= tot; i++) {
        rec[i][0] = rec[i][1] = 0;
        for (int j = 1; j <= tot; j++) {
            w[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int a = edge[i].fi, b = edge[i].se.fi;
        ll c = edge[i].se.se;
        ans[color[a] + color[b]] += c;
        if (id[a] && id[b]) w[id[a]][id[b]] += c, w[id[b]][id[a]] += c;
        if (!id[a]) vec[a].pb(mp(b, c));
        else rec[id[a]][color[b]] += c;
        if (!id[b]) vec[b].pb(mp(a, c));
        else rec[id[b]][color[a]] += c;
    }
}

void change(int x) {
    if (id[x]) {
        ans[color[x] + 0] -= rec[id[x]][0];
        ans[color[x] + 1] -= rec[id[x]][1];
        ans[(color[x] ^ 1) + 0] += rec[id[x]][0];
        ans[(color[x] ^ 1) + 1] += rec[id[x]][1];
        for (int i = 1; i <= tot; i++) {
            rec[i][0] += w[i][id[x]] * (color[x] ? 1 : -1), rec[i][1] += w[i][id[x]] * (color[x] ? -1 : 1);
        }
    } else {
        for (int i = 0; i < vec[x].size(); i++) {
            int v = vec[x][i].fi;
            ans[(color[x] ^ 1) + color[v]] += vec[x][i].se;
            ans[color[x] + color[v]] -= vec[x][i].se;
            if (id[v]) {
                rec[id[v]][color[x]] -= vec[x][i].se;
                rec[id[v]][color[x] ^ 1] += vec[x][i].se;
            }
        }
    }
    color[x] ^= 1;
}

int main() {
    int Case = 1;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) scanf("%d", &color[i]);
        memset(deg, 0, sizeof(deg));
        for (int i = 0; i < m; i++) {
            int a, b;
            ll c;
            scanf("%d%d%I64d", &a, &b, &c);
            edge[i] = mp(a, mp(b, c));
            deg[a]++, deg[b]++;
        }
        init();
        int a, b, q;
        char cmd[20];
        scanf("%d", &q);
        printf("Case %d:\n", Case++);
        while (q--) {
            scanf("%s", cmd);
            if (cmd[0] == 'A') {
                scanf("%d%d", &a, &b);
                printf("%I64d\n", ans[a + b]);
            } else {
                scanf("%d", &a);
                change(a);
            }
        }
    }
    return 0;
}
