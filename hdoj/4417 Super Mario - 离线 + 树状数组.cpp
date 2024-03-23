#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 111111;

int n, m;
struct BIT {
    int c[N];
    int lowbit(int x) { return x & (-x); }
    void clear() { memset(c, 0, sizeof(int) * (n + 1)); }
    void add(int x) { for (int i = x; i <= n; i += lowbit(i)) c[i]++; }
    int sum(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) res += c[i];
        return res;
    }
} bit;

struct Query {
    int x;
    int qid;
    int l, r;
    Query() {}
    Query(int x, int qid, int l, int r) : x(x), qid(qid), l(l), r(r) {}
    bool operator<(const Query &q) const {
        if (x != q.x) return x < q.x;
        return qid < q.qid;
    }
} query[N << 1];

int ans[N];

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        int x;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            query[i] = Query(x, 0, i, i);
        }
        for (int i = 1; i <= m; i++) {
            int L, R;
            scanf("%d%d%d", &L, &R, &x);
            L++, R++;
            query[n + i] = Query(x, i, L, R);
        }
        sort(query + 1, query + 1 + n + m);
        bit.clear();
        for (int i = 1; i <= n + m; i++) {
            const Query &q = query[i];
            //cout << q.x << " " << q.qid << " " << q.l << " " << q.r << endl;
            if (q.qid == 0) {
                bit.add(q.l);
            } else {
                ans[q.qid] = bit.sum(q.r) - bit.sum(q.l - 1);
                //cout << bit.sum(q.r) << " " << bit.sum(q.l - 1) << endl;
            }
        }
        printf("Case %d:\n", Case++);
        for (int i = 1; i <= m; i++) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
