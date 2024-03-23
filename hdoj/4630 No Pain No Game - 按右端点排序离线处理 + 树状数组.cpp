#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
#define lowbit(x) ((x) & (-x))
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

const int N = 55555;
int c[N];
pair<pii, int> a[N * 10], b[N];
int pos[N], d[N], ans[N];
int n, m;
bool cmp(const pair<pii, int> &a, const pair<pii, int> &b) {
    return a.fi.se < b.fi.se;
}

void modify(int x, int val) {
    for (int i = x; i; i -= lowbit(i)) {
        c[i] = max(c[i], val);
    }
}

int query(int x) {
    int res = 0;
    for (int i = x; i <= n; i += lowbit(i)) {
        res = max(res, c[i]);
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d", &n);
        for (int i = 1, x; i <= n; i++) {
            c[i] = 0;
            scanf("%d", &x);
            pos[x] = i;
        }
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &b[i].fi.fi, &b[i].fi.se);
            b[i].se = i;
        }
        sort(b, b + m, cmp);
        int tot = 0;
        for (int i = 2; i * 2 <= n; i++) {
            int t = 0;
            for (int j = i; j <= n; j += i) {
                d[t++] = pos[j];
            }
            sort(d, d + t);
            for (int j = 0; j < t - 1; j++) {
                a[tot++] = mp(mp(d[j], d[j + 1]), i);
            }
        }
        sort(a, a + tot, cmp);
        int p = 0;
        for (int i = 0; i < m; i++) {
            while (p < tot && a[p].fi.se <= b[i].fi.se) modify(a[p].fi.fi, a[p].se), p++;
            if (b[i].fi.fi == b[i].fi.se) ans[b[i].se] = 0;
            else ans[b[i].se] = max(query(b[i].fi.fi), 1);
        }
        for (int i = 0; i < m; i++) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}

