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
const int N = 111;
int a[N];
int n, f;
bool visit[N];
int ans[N], ansTot;
bool between(int a, int b, int x) {
    if(x >= min(a, b) && x <= max(a, b)) return true;
    return false;
}

void go(int &curFloor) {
    int nextFloor;
    for(int i = 0; i < n; i++) {
        if(!visit[i]) {
            nextFloor = a[i];
            break;
        }
    }
    int que[N], tot = 0;
    for(int i = 0; i < n; i++) {
        if(!visit[i] && between(nextFloor, curFloor, a[i])) {
            que[tot++] = a[i];
            visit[i] = true;
        }
    }
    sort(que, que + tot);
    if(curFloor > nextFloor) reverse(que, que + tot);
    for(int i = 0; i < tot; i++) {
        ans[ansTot++] = que[i];
    }
    curFloor = nextFloor;
}

int main() {
    while(cin >> n >> f) {
        for(int i = 0; i < n; i++) cin >> a[i];
        ansTot = 0;
        memset(visit, false, sizeof(visit));
        while(ansTot < n) {
            go(f);
        }
        for(int i = 0; i < n; i++) {
            printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
