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
int n, m;
void init() {
    for (int i = 0; i < N; i++) {
        fa[i] = i;
    }
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    fa[a] = b;
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        init();
        while (m--) {
            int a, b;
            cin >> a >> b;
            n -= Union(--a, --b);
        }
        cout << n << endl;
    }
    return 0;
}
