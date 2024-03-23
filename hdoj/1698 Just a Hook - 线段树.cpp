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
#define MAX 100005
int stick[MAX<<2], n, m;
int lazy[MAX<<2];

void pushup(int p) {
    stick[p] = stick[lc(p)] + stick[rc(p)];
}

void pushdown(int p, int len) {
    if(lazy[p]) {
        lazy[lc(p)] = lazy[rc(p)] = lazy[p];
        stick[lc(p)] = (len - (len >> 1)) * lazy[p];
        stick[rc(p)] = (len >> 1) * lazy[p];
        lazy[p] = 0;
    }
}

void build(int l, int r, int p) {
    lazy[p] = 0;
    if(l == r) {
        stick[p] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lc(p));
    build(mid + 1, r, rc(p));
    pushup(p);
}

void update(int L, int R, int c, int l, int r, int p) {
    if(L <= l && r <= R) {
        lazy[p] = c;
        stick[p] = c * (r - l + 1);
        return;
    }
    pushdown(p, r - l + 1);
    int mid = (l + r) >> 1;
    if(L <= mid) update(L, R, c, l, mid, lc(p));
    if(R > mid) update(L, R, c, mid + 1, r, rc(p));
    pushup(p);
}

int main() {
    int T, Case = 1;
    int x, y, z;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        build(1, n, 1);
        while(m--) {
            scanf("%d%d%d", &x, &y, &z);
            update(x, y, z, 1, n, 1);
        }
        printf("Case %d: The total value of the hook is %d.\n", Case++, stick[1]);
    }
    return 0;
}
