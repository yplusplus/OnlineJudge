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
#define MAX 50005
int seg[MAX<<2];
int n;
void pushup(int p) {
    seg[p] = seg[lc(p)] + seg[rc(p)];
}

void build(int l, int r, int p) {
    if(l == r) {
        scanf("%d", &seg[p]);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lc(p));
    build(mid + 1, r, rc(p));
    pushup(p);
}

int query(int L, int R, int l, int r, int p) {
    if(L == l && R == r) return seg[p];
    int mid = (l + r) >> 1;
    if(L > mid) return query(L, R, mid + 1, r, rc(p));
    else if(R <= mid) return query(L, R, l, mid, lc(p));
    else return query(L, mid, l, mid, lc(p)) + query(mid + 1, R, mid + 1, r, rc(p));
}

void update(int x, int val, int l, int r, int p) {
    if(l == r) {
        seg[p] += val;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) update(x, val, l, mid, lc(p));
    else update(x, val, mid + 1, r, rc(p));
    pushup(p);
}

int main() {
    int T, Case = 1, a, b;
    char str[10];
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        build(1, n, 1);
        printf("Case %d:\n", Case++);
        while(1) {
            scanf("%s", str);
            if(str[0] == 'E') break;
            else {
                scanf("%d%d", &a, &b);
                if(str[0] == 'Q') printf("%d\n", query(a, b, 1, n, 1));
                else if(str[0] == 'A') update(a, b, 1, n, 1);
                else update(a, -b, 1, n, 1);
            }
        }
    }
    return 0;
}

