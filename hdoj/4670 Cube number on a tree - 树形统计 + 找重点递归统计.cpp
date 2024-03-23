#pragma comment(linker, "/STACK:10006777216")
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

map<ll, int> counter;
const int N = 55555;
const int M = 33;
int n, m;
ll prime[M];
int cnt[N][M];
bool visit[N];
int son[N], size[N];
int all;
vector<int> vec[N];
int center;
ll que[N];
int tail;
ll ans;
ll hash(int cnt[]) {
    ll res = 0;
    for (int i = 0; i < m; i++) {
        res <<= 2;
        res += cnt[i];
    }
    return res;
}

ll GetReverseValue(int cnt[]) {
    ll res = 0;
    for (int i = 0; i < m; i++) {
        res <<= 2;
        if (cnt[i]) {
            res += 3 - cnt[i];
        }
    }
    return res;
}

void GetCenter(int u, int fa) {
    son[u] = 1;
    size[u] = 0;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa || visit[v]) continue;
        GetCenter(v, u);
        son[u] += son[v];
        size[u] = max(size[u], son[v]);
    }
    size[u] = max(size[u], all - son[u]);
    if (center == -1 || size[center] > size[u]) center = u;
}

void dfs(int u, int fa, int facnt[], int root) {
    int ucnt[2][M];
    for (int i = 0; i < m; i++) {
        ucnt[0][i] = (cnt[u][i] + facnt[i]) % 3;
        ucnt[1][i] = (ucnt[0][i] + cnt[root][i]) % 3;
    }
    ll hashValue = hash(ucnt[1]);
    que[tail++] = hashValue;
    ll rev = GetReverseValue(ucnt[0]);
    if (counter.count(rev)) ans += counter[rev];
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (v == fa || visit[v]) continue;
        dfs(v, u, ucnt[0], root);
    }
}

void calc(int u) {
    ll hashValue = hash(cnt[u]);
    if (hashValue == 0) ans++;
    counter[hashValue]++;
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) {
            tail = 0;
            dfs(v, u, cnt[0], u);
            for (int i = 0; i < tail; i++) counter[que[i]]++;
        }
    }
}

void solve(int u, int sum) {
    all = sum;
    center = -1;
    GetCenter(u, -1);
    u = center;
    visit[u] = true;
    counter.clear();
    calc(u);
    for (int i = 0; i < vec[u].size(); i++) {
        int v = vec[u][i];
        if (!visit[v]) {
            solve(v, son[v]);
        }
    }
}

int main() {
    while (~scanf("%d", &n)) {
        scanf("%d", &m);
        for (int i = 0; i < m; i++) scanf("%I64d", &prime[i]);        
        for (int i = 1; i <= n; i++) {
            ll x;
            scanf("%I64d", &x);
            vec[i].clear();
            memset(cnt[i], 0, sizeof(cnt[i]));
            for (int j = 0; j < m; j++) {
                while (x % prime[j] == 0) {
                    x /= prime[j];
                    cnt[i][j] = (cnt[i][j] + 1) % 3;
                }
            }
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            vec[a].pb(b);
            vec[b].pb(a);
        }
        ans = 0;
        memset(visit, false, sizeof(visit));
        solve(1, n);
        printf("%I64d\n", ans);
    }
    return 0;
}

