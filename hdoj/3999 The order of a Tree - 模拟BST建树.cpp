#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 100050

struct Tree {
    int val, l, r;
    void init(int _val) {
        val = _val, l = r = -1;
    }
}T[maxn];
int tot, tot1;
int n, key, head;
int ans[maxn];
void insert(int &u, int key) {
    if(u == -1) {
        u = tot;
        T[tot++].init(key);
    } else if(key < T[u].val) insert(T[u].l, key);
    else insert(T[u].r, key);
}

void dfs(int u) {
    if(u == -1) return;
    ans[tot1++] = T[u].val;
    dfs(T[u].l);
    dfs(T[u].r);
}

int main() {
    while(~scanf("%d", &n)) {
        tot = tot1 = 0;
        head = -1;
        for(int i = 0; i < n; i++) {
            scanf("%d", &key);
            insert(head, key);
        }
        dfs(0);
        printf("%d", ans[0]);
        for(int i = 1; i < tot1; i++) printf(" %d", ans[i]);
        printf("\n");
    }
    return 0;
}
