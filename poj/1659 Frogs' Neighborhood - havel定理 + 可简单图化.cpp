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
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;

const int N = 15;
int n;
int g[N][N];
struct Node {
    int id, d;
    Node() {}
    Node(int id, int d) : id(id), d(d) {}
    bool operator < (const Node &x) const { return d > x.d; }
} node[N];

bool solve() {
    for (int i = 0; i < n; i++) {
        sort(node + i, node + n);
        int cnt = node[i].d;
        for (int j = i + 1; j < n && cnt; j++, cnt--) {
            if (--node[j].d < 0) return false;
            g[node[i].id][node[j].id] = g[node[j].id][node[i].id] = 1;
        }
        if (cnt) return false;
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0, d; i < n; i++) {
            scanf("%d", &d);
            node[i] = Node(i, d);
        }
        memset(g, 0, sizeof(g));
        if (solve()) {
            puts("YES");
            for (int i = 0; i < n; i++) 
                for (int j = 0; j < n; j++)
                    printf("%d%c", g[i][j], j == n - 1 ? '\n' : ' ');
        } else puts("NO");
        if (T) puts("");
    }
    return 0;
}
