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
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
#define maxn 210
int n, T;
int cnt[maxn], tot;
int dp[40010];
struct Node {
    int x, y, dis, t, v;
    Node(){}
    Node(int _x, int _y, int _t, int _v) {
        x = _x, y = _y, dis = x * x + y * y;
        t = _t, v = _v;
    }
    bool operator<(const Node &a) const {
        if(x * a.y == y * a.x) return dis < a.dis;
        return x * a.y > y * a.x; 
    }
}p[maxn], l[maxn][maxn];
struct State{
    int t, v;
    State(){}
    State(int _t, int _v) {
        t = _t, v = _v;
    }
}sum[maxn][maxn];

bool check(int i, int j) {
    if(p[i].x * p[j].y == p[i].y * p[j].x) return true;
    return false;
}
int main() {
    int x, y, t, v;
    int Case = 1;
    while (~scanf("%d%d", &n, &T)) {
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &x, &y, &t, &v);
            p[i] = Node(x, y, t, v);
        }
        sort(p, p + n);
        tot = 0;
        for(int i = 0; i < n; i++) {
            if(i != 0 && !check(i, i - 1)) tot++;
            l[tot][cnt[tot]++] = p[i];
        }
        for(int i = 0; i <= tot; i++) {
            sum[i][0] = State(0, 0);
            for(int j = 0; j < cnt[i]; j++) {
                sum[i][j+1] = State(sum[i][j].t + l[i][j].t, sum[i][j].v + l[i][j].v);
            }
        }
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i <= tot; i++) {
            for(int j = T; j > 0; j--) {
                for(int k = 0; k <= cnt[i]; k++) {
                    if(j < sum[i][k].t) break;
                    dp[j] = max(dp[j], dp[j-sum[i][k].t] + sum[i][k].v);
                }
            }
        }
        printf("Case %d: %d\n", Case++, dp[T]);
    }
    return 0;
}
