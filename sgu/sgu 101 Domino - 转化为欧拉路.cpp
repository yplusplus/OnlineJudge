#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 110
int eh[10], tot;
int deg[10];
stack<int> s;
bool visit[maxn];
int n, root;
struct Edge {
    int v, next, id, tag;
}et[maxn*2];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, int id, int tag) {
    Edge e = {v, eh[u], id, tag};
    et[tot] = e;
    eh[u] = tot++;
}

void dfs(int u) {
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v, id = et[i].id;
        if(!visit[id]) {
            visit[id] = true;
            dfs(v);
            s.push(i);
        }
    }
}

int main() {
    while(~scanf("%d", &n)) {
        init();
        memset(deg, 0, sizeof(deg));
        while(!s.empty()) s.pop();
        int root = -1;
        for(int i = 1; i <= n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            deg[a]++, deg[b]++;
            addedge(a, b, i, 0);
            addedge(b, a, i, 1);
            root = a;
        }
        int cnt = 0;
        for(int i = 0; i < 7; i++) {
            if(deg[i] & 1) cnt++, root = i;
        }
        memset(visit, false, sizeof(visit));
        if(cnt != 0 && cnt != 2) puts("No solution");
        else {
            dfs(root);
            if(s.size() != n) puts("No solution");
            else {
                while(!s.empty()) {
                    int id = s.top();
                    s.pop();
                    printf("%d %c\n", et[id].id, et[id].tag ? '-' : '+');
                }
            }
        }
    }
    return 0;
}
