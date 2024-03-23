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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

const int inf = 1 << 30;
#define maxn 1500
#define maxm 1000000
int n, m, s, t;
int eh[maxn], low[maxn], dist[maxn], pre[maxn], cur[maxn], tot, cnt[maxn];
struct Edge {
	int u, v, cap, flow, next;
}et[maxm];
void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}
void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}
void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}
int isap(int s, int t, int n){
	int u, v, now, flow = 0;
	memset(dist, 0, sizeof(dist)); 
	memset(low, 0, sizeof(low));
	memset(cnt, 0, sizeof(cnt));
	for(u = 0 ; u <= n ; u ++) cur[u] = eh[u];
	low[s] = inf, cnt[0] = n, u = s;
	while(dist[s] < n) {
		for(now = cur[u]; now != -1; now = et[now].next)
			if(et[now].cap - et[now].flow && dist[u] == dist[ v = et[now].v ] + 1 ) break;
		if(now != -1) {
			cur[u] = pre[v] = now;
			low[v] = min(et[now].cap - et[now].flow, low[u]);
			u = v;
			if(u == t) {
				for(; u != s; u = et[pre[u]].u){
					et[pre[u]].flow += low[t];
					et[pre[u]^1].flow -= low[t];
				}
				flow += low[t]; low[s] = inf;
			}
		} else {
			if(--cnt[dist[u]] == 0) break;
			dist[u] = n, cur[u] = eh[u];
			for(now = eh[u]; now != -1; now = et[now].next)
				if(et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1)
					dist[u] = dist[ et[now].v ] + 1;
			cnt[dist[u]]++;
			if(u != s) u = et[pre[u]].u;
		}
	}
	return flow;
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        s = 0, t = n + 500 + 1;
        int sum = 0;
        for(int i = 1; i <= n; i++) {
            int p, start, end;
            scanf("%d%d%d", &p, &start, &end);
            sum += p;
            addedge(s, i, p);
            for(int j = start; j <= end; j++) {
                addedge(i, n + j, 1);
            }
        }
        printf("Case %d: ", Case++);
        for(int i = 1; i <= 500; i++) addedge(i + n, t, m);
        if(sum == isap(s, t, 2 + n + 500)) puts("Yes");
        else puts("No");
        cout << endl;
    }
    return 0;
}
