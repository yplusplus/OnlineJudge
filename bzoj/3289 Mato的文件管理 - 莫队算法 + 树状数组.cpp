#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 55555;
const int M = 233;
int a[N], n, m;
int ans[N];

struct Query {
    int qid, l, r, x;
    Query() {}
    Query(int qid, int l, int r) : qid(qid), l(l), r(r) {}
    bool operator<(const Query &q) const {
        if (x != q.x) return x < q.x;
        return r < q.r;
    }
} querys[N];

struct BIT {
    int c[N];
    int lowbit(int x) { return x & (-x); }
    void add(int x, int v) { for (int i = x; i <= n; i += lowbit(i)) c[i] += v; }
    int sum(int x) { int res = 0; for (int i = x; i; i -= lowbit(i)) res += c[i]; return res; }
    void clear() { memset(c, 0, sizeof(c)); }
} bit;

int main() {

    scanf("%d", &n);
    vector<int> vec(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        vec[i - 1] = a[i];
    }

    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &querys[i].l, &querys[i].r);
        querys[i].qid = i;
        querys[i].x = querys[i].l / M;
    }

    sort(querys, querys + m);
    int l = 1, r = 0;
    int inv = 0;
    bit.clear();
    for (int i = 0; i < m; i++) {
        const Query &q = querys[i];
        while (r < q.r) { r++; inv += (r - l) - bit.sum(a[r]); bit.add(a[r], 1); }
        while (r > q.r) { bit.add(a[r], -1); inv -= (r - l) - bit.sum(a[r]); r--; }
        while (l < q.l) { bit.add(a[l], -1); inv -= bit.sum(a[l] - 1); l++; }
        while (l > q.l) { l--; inv += bit.sum(a[l] - 1); bit.add(a[l], 1); }
        ans[q.qid] = inv;
    }

    for (int i = 0; i < m; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
