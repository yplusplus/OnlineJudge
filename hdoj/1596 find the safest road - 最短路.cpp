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

const int N = 1111;
int n, q;
double cost[N][N];
bool visit[N];
double dist[N];

double spfa(int s, int t) {
    queue<int> que;
    for (int i = 0; i < n; i++) visit[i] = false, dist[i] = -dinf;
    que.push(s);
    dist[s] = 1.0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        visit[u] = false;
        for (int v = 0; v < n; v++) {
            if (u != v && dist[v] < dist[u] * cost[u][v]) {
                dist[v] = dist[u] * cost[u][v];
                if (!visit[v]) {
                    visit[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dist[t];
}

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%lf", &cost[i][j]);
            }
        }
        int s, t;
        scanf("%d", &q);
        while (q--) {
            scanf("%d%d", &s, &t);
            s--, t--;
            double ans = spfa(s, t);
            if (ans <= 0) puts("What a pity!");
            else printf("%.3f\n", ans);
        }
    }
    return 0;
}
