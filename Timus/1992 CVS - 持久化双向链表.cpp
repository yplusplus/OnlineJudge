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

const int N = 555555;
int alloc;
int n, m;
int status[N];
struct Node {
    int l, r, val;
    Node() {}
    Node(int l, int r, int val) : l(l), r(r), val(val) {}
    Node(const Node &x) { *this = x; }
} node[N];

int main() {
    char cmd[20];
    while (~scanf("%d%d", &n, &m)) {
        alloc = 0;
        int id = 0, a, b, now;
        node[++alloc] = Node(0, 0, 0);
        status[++id] = alloc;
        for (int i = 0; i < n; i++) {
            scanf("%s%d", cmd, &a);
            now = status[a];
            if (strcmp(cmd, "learn") == 0) {
                scanf("%d", &b);
                node[++alloc] = Node(now, 0, b);
                status[a] = alloc;
            } else if (strcmp(cmd, "rollback") == 0) {
                node[++alloc] = Node(node[node[now].l].l, now, node[node[now].l].val);
                status[a] = alloc;
            } else if (strcmp(cmd, "relearn") == 0) {
                node[++alloc] = Node(now, node[node[now].r].r, node[node[now].r].val);
                status[a] = alloc;
            } else if (strcmp(cmd, "clone") == 0) {
                node[++alloc] = Node(node[now]);
                status[++id] = alloc;
            } else if (strcmp(cmd, "check") == 0) {
                if (node[now].val) printf("%d\n", node[now].val);
                else puts("basic");
            }
        }
    }
    return 0;
}
