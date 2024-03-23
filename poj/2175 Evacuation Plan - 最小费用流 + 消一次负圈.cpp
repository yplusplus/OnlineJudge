#include "iostream"
#include "cstdio"
#include "queue"
#include "cmath"
#include "cstring"
using namespace std;
const int INF = 99999999;
#define maxn 210
#define maxm 50005
#define MAX 105
int s, t, n, m;
struct node {
	int x, y;
}a[MAX], b[MAX];

struct Edge {
	int u, v, cost, cap, flow, next;
}et[maxm];
int plan[MAX][MAX], flow[MAX]， num[MAX], cap[MAX], maz[MAX][MAX];
int tot, eh[maxn], cnt[maxn], dist[maxn], pre[maxn];
bool visit[maxn];
void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cost, int cap, int flow) {
	Edge E = {u, v, cost, cap, flow, eh[u]};
	et[tot] = E;
	eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap, int flow) {
	add(u, v, cost, cap, flow), add(v, u, -cost, 0, -flow);
}

int getdist(node &a, node &b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool spfa(int s, int n, int n1) {
	for(int i = 0; i <= n; i++) visit[i] = false, dist[i] = INF, cnt[i] = 0, pre[i] = -1;
	dist[s] = 0, visit[s] = true, cnt[s]++;
	queue<int> que;
	que.push(s);
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for(int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v, cap = et[i].cap, flow = et[i].flow, cost = et[i].cost;
			if(cap - flow && dist[v] > cost + dist[u]) {
				dist[v] = cost + dist[u];
				pre[v] = u;		//这里记录当前弧的下标亦可 既pre[v] = i,后面只需相应改一下就可以了
				if(!visit[v]) {
					visit[v] = true;
					que.push(v);
					cnt[v]++;
					if(cnt[v] >= n) {	//有负环
						memset(visit, false, sizeof(visit));
						u = v;
						while(!visit[u]) {	//找到负环上任意一个点
							visit[u] = true;
							u = pre[u];
						}
						int end = u;
						u = pre[v = u];
						do {	//更改流量
							if(u < v && v != t) plan[u][v - n1]++;
							else if(u > v && u != t) plan[v][u - n1]--;
							u = pre[v = u];
						}while(v != end);
						return false;
					}
				}
			}
		}
	}
	return true;
}

void build() {
	init();
	for(int j = 1; j <= m; j++)
		addedge(j + n, t, 0, cap[j], flow[j]);
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= m; j++)
			addedge(i, j + n, maz[i][j], INF, plan[i][j]);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d%d%d", &a[i].x, &a[i].y, &num[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d%d%d", &b[i].x, &b[i].y, &cap[i]);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			maz[i][j] = getdist(a[i], b[j]) + 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> plan[i][j];
		}
	}
	for(int j = 1; j <= m; j++) {
		flow[j] = 0;
		for(int i = 1; i <= n; i++) {
			flow[j] += plan[i][j];
		}
	}
	t = n + m + 1;
	build();
	if(spfa(t, t, n)) cout << "OPTIMAL" << endl;
	else {
		cout << "SUBOPTIMAL" << endl;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				printf("%d ", plan[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}