#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;
const int N = 111111;
const int MAX_CNT = 35;
const ULL MOD = 9223372034707292160ULL;

ULL Add(ULL a, ULL b) {
    return (a + b) % MOD;
}

ULL QuickProduct(ULL a, ULL b) {
    ULL res = 0;
    while (b) {
        if (b & 1) res = Add(res, a);
        b >>= 1;
        a = Add(a, a);
    }
    return res;
}

struct Node {
    ULL sum;
    int cnt;
} node[N << 2];

struct SegTree {
    void build(int p, int l, int r) {
        node[p].cnt = 0;
        if (l == r) {
            cin >> node[p].sum;
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        PushUp(p, l, r);
    }
    void PushUp(int p, int l, int r) {
        node[p].sum = (node[p << 1].sum + node[p << 1 | 1].sum) % MOD;
    }
    ULL Query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return node[p].sum;
        }
        int mid = l + r >> 1;
        ULL ret = 0;
        if (L <= mid) ret = Add(ret, Query(p << 1, l, mid, L, R));
        if (mid < R) ret = Add(ret, Query(p << 1 | 1, mid + 1, r, L, R));
        return ret;
    }
    void Modify(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            if (node[p].cnt >= MAX_CNT) return;
            node[p].cnt++;
        }
        if (l == r) {
            node[p].sum = QuickProduct(node[p].sum, node[p].sum);
            //cout << l << " " << node[p].sum << endl;
            return;
        }
        int mid = l + r >> 1;
        if (L <= mid) Modify(p << 1, l, mid, L, R);
        if (mid < R) Modify(p << 1 | 1, mid + 1, r, L, R);
        PushUp(p, l, r);
    }
} seg_tree;

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        ULL s = 0;
        seg_tree.build(1, 1, n);
        printf("Case #%d:\n", Case++);
        for (int i = 0; i < m; i++) {
            int L, R;
            scanf("%d%d", &L, &R);
            s = Add(s, seg_tree.Query(1, 1, n, L, R));
            cout << s << endl;
            seg_tree.Modify(1, 1, n, L, R);
        }
    }
    return 0;
}
