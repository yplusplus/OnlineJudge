#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define MAX 100050
#define ll long long
ll lazy[MAX<<2], sum[MAX<<2];
int n, q;

void pushup(int p) {
    sum[p] = sum[lc(p)] + sum[rc(p)];
}

void pushdown(int p, int len) {
    if(lazy[p]) {
        lazy[lc(p)] += lazy[p];
        lazy[rc(p)] += lazy[p];
        sum[lc(p)] += (len - (len >> 1)) * lazy[p];
        sum[rc(p)] += (len >> 1) * lazy[p];
        lazy[p] = 0;
    }
}

void build(int l, int r, int p) {
    lazy[p] = 0;
    if(l == r) {
        scanf("%lld", &sum[p]);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lc(p));
    build(mid + 1, r, rc(p));
    pushup(p);
}

void update(int L, int R, ll c, int l, int r, int p) {
    if(L <= l && r <= R) {
        lazy[p] += c;
        sum[p] += c * (r - l + 1);
        return;
    }
    pushdown(p, r - l + 1);
    int mid = (l + r) >> 1;
    if(L <= mid) update(L, R, c, l, mid, lc(p));
    if(R > mid) update(L, R, c, mid + 1, r, rc(p));
    pushup(p);
}

ll query(int L, int R, int l, int r, int p) {
    ll res = 0;
    if(L <= l && r <= R) {
        return sum[p];
    }
    pushdown(p, r - l + 1);
    int mid = (l + r) >> 1;
    if(L <= mid) res += query(L, R, l, mid, lc(p));
    if(R > mid) res += query(L, R, mid + 1, r, rc(p));
    pushup(p);
    return res; 
}

int main() {
    char str[5];
    int a, b;
    ll c;
    while(~scanf("%d%d", &n, &q)) {
        build(1, n, 1);
        while(q--) {
            scanf("%s%d%d", str, &a, &b);
            if(str[0] == 'Q') printf("%lld\n", query(a, b, 1, n, 1));
            else {
                scanf("%lld", &c);
                update(a, b, c, 1, n, 1);
            }
        }
    }
    return 0;
}
