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
#define maxn 1500 
#define maxm 1000500
int n;
int eh[maxn], tot;
bool visit[maxn];
int match[maxn];

struct Edge {
    int u, v, next;
}et[maxm];

struct Point {
    int w, l, h;
}p[maxn];

void init() {
    tot = 0;
    memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v) {
    Edge e = {u, v, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

bool dfs(int u) {
    for(int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (!visit[v]) {
            visit[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int Match() {//二分图匹配
    int cnt = 0;
    memset(match, -1, sizeof (match));
    for (int u = 1; u <= 2 * n; u++) {
        memset(visit, false, sizeof (visit));
        if (dfs(u)) cnt++; //每找到一条增广路，匹配数+1
    }
    return cnt; //返回最大匹配数
}

bool check(const Point &a, const Point &b) {
    return a.h < b.h && a.l < b.l && a.w < b.w;
}

void build() {
    init();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(check(p[i], p[j])) addedge(i + n, j);
        }
    }
}

int main() {
    while(~scanf("%d", &n) && n) {
        for(int i = 0; i < n; i++) scanf("%d%d%d", &p[i].w, &p[i].l, &p[i].h);
        build();
        printf("%d\n", n - Match());
    }
    return 0;
}
