#include "iostream"
#include "cstdio"
#include "cstring"
#include "queue"
#include "vector"
using namespace std;
#define maxn 1510
#define ll long long
int n, tot;
ll ans[maxn];
void init() {
    priority_queue<ll, vector<ll>, greater<ll> > que;
    que.push(1);
    tot = 0, ans[0] = 0;
    while(!que.empty()) {
        ll tmp = que.top();
        que.pop();
        if(tmp == ans[tot]) continue;
        ans[++tot] = tmp;
        que.push(tmp * 2), que.push(tmp * 3), que.push(tmp * 5);
        if(tot == maxn - 1) break;
    }
}

int main() {
    init();
    while(~scanf("%d", &n)) {
        if(n == 0) break;
        printf("%lld\n", ans[n]);
    }
    return 0;
}
