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
#define MAX 10000
int prime[1300], tot;
bool maz[1300][1300];
int ans[1300][1300], visit[1300];
int s, t;

bool check(int a, int b) {
    int cnt = 0;
    for(int i = 0; i < 4; i++) {
        if(a % 10 != b % 10) cnt++;
        a /= 10, b /= 10;
    }
    if(cnt == 1) return true;
    return false;
}

int bfs() {
    memset(visit, -1, sizeof(visit));
    queue<int> que;
    que.push(s);
    visit[s] = 0;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        if(u == t) return visit[t];
        for(int v = 0; v < tot; v++) {
            if(maz[u][v] && visit[v] == -1) {
                visit[v] = visit[u] + 1;
                que.push(v);
            }
        }
    }
    return -1;
}

void init() {
    tot = 0;
    bool isprime[MAX];
    memset(isprime, true, sizeof(isprime));
    for(int i = 3; i < MAX; i += 2) {
        if(isprime[i]) {
            if(i > 1000) prime[tot++] = i;
            if(i * i < MAX)
                for(int j = i + i; j < MAX; j += i) isprime[j] = false;
        }
    }
    for(int i = 0; i < tot; i++) {
        for(int j = i + 1; j < tot; j++) {
            maz[i][j] = maz[j][i] = check(prime[i], prime[j]);
        }
    }
}


int main() {
    int a, b, T;
    init();
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &a, &b);
        for(int i = 0; i < tot; i++) {
            if(a == prime[i]) s = i;
            if(b == prime[i]) t = i;
        }
        int ans = bfs();
        if(ans != -1) printf("%d\n", ans);
        else printf("Impossible\n");
    }
    return 0;
}
