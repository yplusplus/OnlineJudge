#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
using namespace std;
#define maxn 105
#define maxm 10050
const int inf = 1 << 30;
int ans, anscost, eh[maxn], tot, low[maxn], p[maxn], dist[maxn]; 
int s, t, ss, tt;
int n, m;
int sum;
int in[maxn], out[maxn];
struct Edge {
    int u, v, cost, cap, flow, next; 
} et[maxm];
bool visit[maxn];

void init() {
    sum = tot = 0;
    memset(eh, -1, sizeof (eh));
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
}

void add(int u, int v, int cost, int cap, int flow) {
    Edge e = {u, v, cost, cap, flow, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap) {
    add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}

bool spfa() {
    queue<int> que;
    memset(visit, false, sizeof (visit));
    memset(p, -1, sizeof (p));
    memset(low, 0, sizeof(low));
    fill(&dist[0], &dist[maxn], inf);
    visit[ss] = true, low[ss] = inf, dist[ss] = 0;
    que.push(ss);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int i = eh[u]; i != -1; i = et[i].next) {
            int v = et[i].v, cost = et[i].cost, cap = et[i].cap, flow = et[i].flow;
            if (flow < cap && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                p[v] = i;
                low[v] = min(low[u], cap - flow);
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dist[tt] != inf;
}

void costflow() {
    ans = 0, anscost = 0;
    while (spfa()) {
        int x = p[tt];
        ans += low[tt];
        anscost += low[tt] * dist[tt];
        while (x != -1) {
            et[x].flow += low[tt];
            et[x^1].flow -= low[tt];
            et[x^1].cost = -et[x].cost;
            x = p[et[x].u];
        }
    }
}

int main() {
	int T, Case = 1;
	int u, v, a, b;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d", &n, &m, &s, &t);
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d%d", &u, &v, &a, &b);
			if(a <= b) {
				sum += a;
				addedge(v, u, b - a, 1);
				in[v]++, out[u]++;
			} else {
				sum += b;
				addedge(u, v, a - b, 1);
			}
		}
		in[s]++, out[t]++;
		ss = 0, tt = n + 1;
		int tmp = 0;
		for(int i = 1; i <= n; i++) {
			addedge(ss, i, 0, in[i]);
			addedge(i, tt, 0, out[i]);
			tmp += in[i];
		}
/*		for(int i = 1; i <= n; i++) {
			if(in[i] >= out[i]) addedge(ss, i, 0, in[i] - out[i]), tmp += in[i] - out[i];
			else addedge(i, tt, 0, out[i] - in[i]);
		}*/
		costflow();
		printf("Case %d: ", Case++);
		if(ans == tmp) printf("%d\n", sum + anscost);
		else printf("impossible\n");
	}
	return 0;
}