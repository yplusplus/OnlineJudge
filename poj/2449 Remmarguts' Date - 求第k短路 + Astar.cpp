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
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 1111
#define maxm 111111
int S, T, K;
int eh1[maxn], eh2[maxn], tot1, tot2;
int n, m;
int dist[maxn], cnt[maxn];
bool visit[maxn];
struct Node {
    int u, len;
    Node(){}
    Node(int _u, int _len) {
        u = _u, len = _len;
    }
    bool operator<(const Node &x) const {
        return len + dist[u] > x.len + dist[x.u];
    }
};
struct Edge {
    int u, v, w, next;
}et1[maxm], et2[maxm];

void init() {
    tot1 = tot2 = 0;
    memset(eh1, -1, sizeof(eh1));
    memset(eh2, -1, sizeof(eh2));
}

void addedge(int u, int v, int w, int eh[], Edge et[], int &tot) {
    Edge e = {u, v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void spfa(int s) {
    memset(visit, false, sizeof(visit));
    for(int i = 1; i <= n; i++) dist[i] = inf;
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    visit[s] = true;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for(int i = eh2[u]; i != -1; i = et2[i].next) {
            int v = et2[i].v, w = et2[i].w;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if(!visit[v]) {
                   que.push(v);
                   visit[v] = true;
               } 
            }
        }
    }
}

int Astar() {
    memset(cnt, 0, sizeof(cnt));
    priority_queue<Node> que;
    que.push(Node(S, 0));
    while(!que.empty()) {
        Node now = que.top();
        que.pop();
        if(cnt[now.u] + 1 > K) continue;
        cnt[now.u]++;
        if(now.u == T && cnt[now.u] == K) return now.len;
        for(int i = eh1[now.u]; i != -1; i = et1[i].next) {
            int v = et1[i].v, w = et1[i].w;
            que.push(Node(v, now.len + w));
        }
    }
    return -1;
}

int main() {
    while(~scanf("%d%d", &n, &m)) {
        init();
        for(int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w, eh1, et1, tot1);
            addedge(v, u, w, eh2, et2, tot2);
        }
        scanf("%d%d%d", &S, &T, &K);
        if(S == T) K++;
        spfa(T);
        int ans = Astar();
        printf("%d\n", ans);
    }
    return 0;
}
