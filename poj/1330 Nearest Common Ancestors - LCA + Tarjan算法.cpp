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
#define maxn 10005
vector<int> tree[maxn], Q[maxn];
int in[maxn], n;
bool visit[maxn];
int fa[maxn];

void init() {
    for(int i = 0; i <= n; i++) fa[i] = i, tree[i].clear(), Q[i].clear();
    memset(visit, false, sizeof(visit));
    memset(in, 0, sizeof(in));
}

int find(int x) {
    if(x == fa[x]) return x;
    else return fa[x] = find(fa[x]);
}

bool un(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    fa[b] = a;
    return true;
}

void Tarjan(int u) {
    int size = tree[u].size();
    for(int i = 0; i < size; i++) {
        Tarjan(tree[u][i]);
        un(u, tree[u][i]);
    }
    visit[u] = true, size = Q[u].size();
    for(int i = 0; i < size; i++) {
        if(visit[Q[u][i]]) {
            printf("%d\n", find(Q[u][i]));
            return;
        }
    }
}

int main() {
    int T, u, v;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        init();
        for(int i = 0; i < n - 1; i++) {
            scanf("%d%d", &u, &v);
            tree[u].pb(v);
            in[v]++;
        }
        scanf("%d%d", &u, &v);
        Q[u].pb(v), Q[v].pb(u);
        int root = -1;
        for(int i = 1; i <= n; i++) {
            if(in[i] == 0) {
                root = i;
                break;
            }
        }
        Tarjan(root);
    }
    return 0;
}
