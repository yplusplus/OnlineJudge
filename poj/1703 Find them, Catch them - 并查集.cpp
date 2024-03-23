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
#include "iomanip"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 200050
int n, m;
int fa[maxn];

void init() {
    for(int i = 0; i < maxn; i++) fa[i] = i;
}

int find(int x) {
    if(x != fa[x]) return fa[x] = find(fa[x]);
    return fa[x];
}

bool un(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    fa[a] = b;
    return true;
}

int main() {
    int T, a, b;
    char op[5];
    scanf("%d", &T);
    while(T--) {
        init();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++) {
            scanf("%s%d%d", op, &a, &b);
            if(op[0] == 'A') {
                if(find(a) == find(b)) printf("In the same gang.\n");
                else if(find(a) == find(b+n)) printf("In different gangs.\n");
                else printf("Not sure yet.\n");
            } else {
                un(a, b + n), un(a + n, b);
            }
        }
    }
    return 0;
}
