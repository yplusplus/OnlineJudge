#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define MAX 200050
int sum[MAX<<2];
int h, w, n;

void pushup(int p) {
    sum[p] = max(sum[lc(p)], sum[rc(p)]);
}

void build(int l, int r, int p) {
    sum[p] = w;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, lc(p));
    build(mid + 1, r, rc(p));
}

int query(int L, int l, int r, int p) {
    if(l == r) {
        sum[p] -= L; // 找到最优位置并更新
        return l;
    }
    int mid = (l + r) >> 1, ans = -1;
    if(L <= sum[lc(p)]) ans = query(L, l, mid, lc(p));
    else ans = query(L, mid + 1, r, rc(p));
    pushup(p);
    return ans;
}

int main() {
    int L;
    while(~scanf("%d%d%d", &h, &w, &n)) {
        if(h > n) h = n;
        build(1, h, 1);
        for(int i = 0; i < n; i++) {
            scanf("%d", &L);
            if(sum[1] < L) printf("-1\n");
            else printf("%d\n", query(L, 1, h, 1));
        }
    }
    return 0;
}
