#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
using namespace std;
#define pb push_back
#define MAX 200050
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
const int inf = 1 << 30;
int grade[MAX<<2], n, m;

void pushup(int p) {
    grade[p] = max(grade[lc(p)], grade[rc(p)]);
}

void build(int l, int r, int p) {
    if(l == r) {
        scanf("%d", &grade[p]);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lc(p));
    build(mid + 1, r, rc(p));
    pushup(p);
}

int query(int L, int R, int l, int r, int p) {
    int res = -inf; 
    if(L == l && R == r) return grade[p];
    int mid = (l + r) >> 1;
    if(L > mid) res = max(res, query(L, R, mid + 1, r, rc(p)));
    else if(R <= mid) res = max(res, query(L, R, l, mid, lc(p)));
    else res = max(res, max(query(L, mid, l, mid, lc(p)), query(mid + 1, R, mid + 1, r, rc(p))));
    return res;
}

void update(int x, int val, int l, int r, int p) {
    if(l == r) {
        grade[p] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) update(x, val, l, mid, lc(p));
    else update(x, val, mid + 1, r, rc(p));
    pushup(p);
}

int main() {
    int a, b;
    char str[10];
    while(~scanf("%d%d", &n, &m)) {
        build(1, n, 1);
        while(m--) {
            scanf("%s%d%d", str, &a, &b);
            if(str[0] == 'Q') printf("%d\n", query(a, b, 1, n, 1));
            else update(a, b, 1, n, 1);
        }
    }
    return 0;
}
