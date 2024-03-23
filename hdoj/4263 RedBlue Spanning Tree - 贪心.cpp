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
int fa[N];
void init() {
    for (int i = 0; i < N; i++) fa[i] = i;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    fa[a] = b;
    return true;
}

vector<pii> blue, red;

int calc(vector<pii> &a) {
    init();
    int cnt = 0;
    for (int i = 0; i < a.size(); i++) {
        cnt += Union(a[i].fi, a[i].se);
    }
    return cnt;
}

int n, m, k;
int main() {
    while (~scanf("%d%d%d", &n, &m, &k), n + m + k) {
        char color[5];
        blue.clear();
        red.clear();
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%s%d%d", color, &a, &b);
            if (color[0] == 'R') red.pb(mp(a, b));
            else blue.pb(mp(a, b));
        }
        int l = n - 1 - calc(red);
        int r = calc(blue);
        //cout << l << " " << r << endl;
        if (k >= l && k <= r) puts("1");
        else puts("0");
    }
    return 0;
}
