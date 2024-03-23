#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define inf 999999999
#define maxn 1005
#define maxm 300005

int n, m, s, t;
int eh[maxn], pre[maxn], cur[maxn], dist[maxn], cnt[maxn], tot, low[maxn];
int ddeh[maxn], tot1, dd[maxn], rddeh[maxn], rdd[maxn], tot2;
bool visit[maxn];
struct Edge {
    int u, v, cap, flow, next;
}et[maxm];

struct Edge1 {
    int u, v, w, next;
}ddet[maxm], rddet[maxm];

void isapinit() {
    tot = tot1 = tot2 = 0;
    memset(eh, -1, sizeof(eh));
    memset(ddeh, -1, sizeof(ddeh));
    memset(rddeh, -1, sizeof(rddeh));
}

void isapadd(int u, int v, int cap, int flow) {
    Edge E = {u, v, cap, flow, eh[u]};
    et[tot] = E;
    eh[u] = tot++;
}

void isapaddedge(int u, int v, int cap) {
    isapadd(u, v, cap, 0), isapadd(v, u, 0, 0);
}

void add1(int u, int v, int w) {
    Edge1 E = {u, v, w, ddeh[u]};
    ddet[tot1] = E;
    ddeh[u] = tot1++;
}

void add2(int u, int v, int w) {
    Edge1 E = {u, v, w, rddeh[u]};
    rddet[tot2] = E;
    rddeh[u] = tot2++;
}

int isap(int s, int t, int n) {
    int u, v, now, flow = 0;
    memset(dist, 0, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    memset(low, 0, sizeof(low));
    for(u = 0; u <= n; u++) cur[u] = eh[u];
    low[s] = inf, cnt[0] = n;
    u = s;
    while(dist[s] < n) {
        for(now = cur[u]; now != -1; now = et[now].next)
            if(et[now].cap - et[now].flow && dist[u] == dist[v = et[now].v] + 1)
                break;
        if(now != -1) {
            cur[u] = pre[v] = now;
            low[v] = min(low[u], et[now].cap - et[now].flow);
            u = v;
            if(u == t) {
                for(; u != s; u = et[pre[u]].u) {
                    et[pre[u]].flow += low[t];
                    et[pre[u]^1].flow -= low[t];
                }
                low[s] = inf, flow += low[t];
            }
        } else {
            if(--cnt[dist[u]] == 0) break;
            dist[u] = n;
            cur[u] = eh[u];
            for(now = cur[u]; now != -1; now = et[now].next)
            if(et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1)
                dist[u] = dist[et[now].v] + 1;
            cnt[dist[u]]++;
        }
    }
    return flow;
}

bool spfa(int s, Edge1 ddet[], int ddeh[], int dd[]) {
    for(int i = 0; i <= n; i++) visit[i] = 0, dd[i] = inf;
    dd[s] = 0, visit[s] = 1;
    queue<int> que;
    que.push(s);
    while(!que.empty()) {
        int u = que.front();
        que.pop(), visit[u] = 0;
        for(int i = ddeh[u]; i != -1; i = ddet[i].next) {
            int v = ddet[i].v;
            if(dd[v] > ddet[i].w + dd[u]) {
                dd[v] = ddet[i].w + dd[u];
                if(!visit[v]) {
                    visit[v] = 1;
                    que.push(v);
                }
            }
        }
    }
    return true;
}

int main() {
    int T, u, v, w;
    scanf("%d", &T);
    while(T--) {
        isapinit();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            add1(u, v, w);
            add2(v, u, w);
        }
        scanf("%d%d", &s, &t);
        spfa(s, ddet, ddeh, dd);
        spfa(t, rddet, rddeh, rdd);
        for(int i = 0; i < tot1; i++) {
            u = ddet[i].u, v = ddet[i].v, w = ddet[i].w;
            if(dd[u] + w + rdd[v] == dd[t])
                isapaddedge(u, v, 1);
        }
        printf("%d\n", isap(s, t, n));
    }
    return 0;
}