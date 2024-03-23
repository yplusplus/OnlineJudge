#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;
const int N = 11111;
int n, k;
bool visit[N];
int ans;
int eh[N], tot;
int dp[N], son[N];
struct Edge {
    int v, w, next;
} et[N << 1];

void init() {
    memset(eh, -1, sizeof(eh));
    tot = 0;
}

void addedge(int u, int v, int w) {
    Edge e = {v, w, eh[u]};
    et[tot] = e;
    eh[u] = tot++;
}

int node[N], node_number;
void _dfs(int u, int fa) {
    node[node_number++] = u;
    son[u] = 1;
    dp[u] = 0;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (v == fa || visit[v]) continue;
        _dfs(v, u);
        son[u] += son[v];
        dp[u] = max(dp[u], son[v]);
    }
}

int GetCenter(int u, int sum) {
    node_number = 0;
    _dfs(u, 0);
    u = -1;
    for (int i = 0; i < node_number; i++) {
        dp[node[i]] = max(dp[node[i]], sum - son[node[i]]);
        if (u == -1 || dp[node[i]] < dp[u]) u = node[i];
    }
    return u;
}

int vv[2][N], v_number0, v_number1;

int calc(int a[], int number) {
    sort(a, a + number);
    int r = number - 1;
    int res = 0;
    for (int i = 0; i < r; i++) {
        while (r && 0LL + a[i] + a[r] > k) r--;
        if (r <= i) break;
        res += r - i;
    }
    return res;
}

void __dfs(int u, int fa, int t) {
    vv[1][v_number1++] = t;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (v == fa || visit[v]) continue;
        __dfs(v, u, t + et[i].w);
    }    
}

void dfs(int u, int sum) {
    u = GetCenter(u, sum);
    visit[u] = true;
    v_number0 = 0;
    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (!visit[v]) {
            v_number1 = 0;
            __dfs(v, u, et[i].w);
            ans -= calc(vv[1], v_number1);
            for (int i = 0; i < v_number1; i++) {
                vv[0][v_number0++] = vv[1][i];
            }
        }
    }
    vv[0][v_number0++] = 0;
    ans += calc(vv[0], v_number0);

    for (int i = eh[u]; i != -1; i = et[i].next) {
        int v = et[i].v;
        if (!visit[v]) {
            dfs(v, son[v]);
        }
    }
}

int main() {
    while (~scanf("%d%d", &n, &k), n + k) {
        init();
        for (int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            addedge(a, b, c);
            addedge(b, a, c);
        }
        ans = 0;
        memset(visit, false, sizeof(visit));
        dfs(1, n);
        printf("%d\n", ans);
    }
    return 0;
}


