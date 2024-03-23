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
const double eps = 1e-10;
const int N = 1111;
int fa[N], sig[N];
double offset[N];
int n, m;
void init () {
    for (int i = 0; i < N; i++) {
        fa[i] = i;
        offset[i] = 0;
        sig[i] = 1;
    }
}

int find(int x) {
    if (x == fa[x]) return x;
    int t = fa[x];
    fa[x] = find(t);
    offset[x] += sig[x] * offset[t];
    sig[x] *= sig[t];
    return fa[x];
}

bool Union(int a, int b, int c) {
    int ra = find(a);
    int rb = find(b);
    if (ra == rb) {
        if (ra == 0 || sig[a] != sig[b]) {
            return fabs(offset[a] + offset[b] - c) < eps;
        } else {
            fa[ra] = 0;
            offset[ra] = 1.0 * (c - offset[a] - offset[b]) / (sig[a] + sig[b]);
            sig[ra] = 1;
            return true;
        }
    }
    if (ra == 0) {
        fa[rb] = ra;
        offset[rb] = 1.0 * (c - offset[a] - offset[b]) * sig[b];
        sig[rb] = -sig[b] * sig[a];
    } else {
        fa[ra] = rb;
        offset[ra] = 1.0 * (c - offset[a] - offset[b]) * sig[a];
        sig[ra] = -sig[b] * sig[a];
    }
    return true;
}

int main() {
    while (cin >> n >> m) {
        init();
        bool found = false;
        int a, b, c;
        while (m--) {
            cin >> a >> b >> c;
            found |= !Union(a, b, c);
        }
        for (int i = 1; i <= n; i++) {
            if (find(i) != 0) found = true;
        }
        if (found) puts("IMPOSSIBLE");
        else {
            for (int i = 1; i <= n; i++) {
                printf("%.2f\n", offset[i]);
            }
        }
    }
    return 0;
}
