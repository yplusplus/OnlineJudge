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
int powTable[5] = {1, 10, 100, 1000, 10000};
int visit[10000];
int s, t;
inline void swap(int &x, int idx) {
    int a = (x % powTable[idx + 1]) / powTable[idx];
    int b = (x % powTable[idx]) / powTable[idx - 1];
    x += 9 * (b - a) * powTable[idx - 1];
}

inline void calc(int &x, int idx, int v) {
    int a = (x % powTable[idx + 1]) / powTable[idx];
    if(a == 1 && v == -1) {
        x += 8 * powTable[idx];
    } else if(a == 9 && v == 1) {
        x -= 8 * powTable[idx];
    } else {
        x += v * powTable[idx];
    }
}

int bfs(int s, int t) {
    memset(visit, -1, sizeof(visit));
    queue<int> que;
    que.push(s);
    visit[s] = 0;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        int x;
        if(u == t) return visit[t];
        for(int i = 1; i < 4; i++) {
            x = u;
            swap(x, i);
            if(visit[x] == -1) {
                visit[x] = visit[u] + 1;
                que.push(x);
            }
        }
        for(int i = 0; i < 4; i++) {
            x = u;
            calc(x, i, 1);
            if(visit[x] == -1) {
                visit[x] = visit[u] + 1;
                que.push(x);
            }
            x = u;
            calc(x, i, -1);
            if(visit[x] == -1) {
                visit[x] = visit[u] + 1;
                que.push(x);
            }
        }
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &s, &t);
        int ans = bfs(s, t);
        cout << ans << endl;
    }
    return 0;
}
