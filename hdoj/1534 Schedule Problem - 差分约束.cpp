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
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 10050
#define maxm 500000
const int inf = 1 << 29;
struct Edge {
    int u, v, cost, next;
} et[maxm];

int eh[maxn], tot, dist[maxn], cnt[maxn];
bool visit[maxn];
int n, m;
int val[maxn];
int s;

void init() {
    tot = 0;
    memset(eh, -1, sizeof (eh));
}

void addedge(int u, int v, int cost) {
    Edge e = {u, v, cost, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

bool spfa(int s) {
    for (int i = 0; i <= n; i++) visit[i] = false, dist[i] = -inf, cnt[i] = 0;//dist[i] = -inf;
    dist[s] = 0, visit[s] = true, cnt[s]++;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop(), visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
          int v = et[i].v, cost = et[i].cost;
            if (dist[v] < cost + dist[u]) {//dis>[v] < cost + dist[u]
                dist[v] = cost + dist[u];
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                    cnt[v]++;
                    if (cnt[v] >= n + 1) return false; 
                }
            }
        }
    }
    return true;
}

int main() {
    string s;
    int Case = 1;
    while(~scanf("%d", &n)) {
        if(!n) break;
        init();
        for(int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            addedge(0, i, 0);
        }
        addedge(1, 0, 0);
        int a, b;
        while(1) {
            cin >> s;
            if(s == "#") break;
            scanf("%d%d", &a, &b);
            if(s == "SAF") addedge(b, a, val[b]);
            else if(s == "FAF") addedge(b, a, val[b] - val[a]);
            else if(s == "SAS") addedge(b, a, 0);
            else if(s == "FAS") addedge(b, a, -val[a]);
        }
        printf("Case %d:\n", Case++);
        if(spfa(0)) {
            for(int i = 1; i <= n; i++) {
                printf("%d %d\n", i, dist[i]);
            }
        } else printf("impossible\n");
        printf("\n");
    }
    return 0;
}
