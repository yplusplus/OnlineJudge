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
const int N = 55555;
struct Node {
    int id, a, b;
    Node(){}
    Node(int _id, int _a, int _b) {
        id = _id, a = _a, b = _b;
    }
    bool operator<(const Node &x) const {
        return a < x.a;
    }
}node[N];
int fa[N], l[N], r[N];
int n, top;
Node s[N];

//裸的笛卡尔树
//在有序的情况下可以用一个栈构造，维护最右边的链，
//每个结点出栈入栈一次，时间复杂度为O(n)。
//该题需要先排序，所以总的时间复杂度为O(nlogn+n)。

int main() {
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            int a, b;
            cin >> a >> b;
            node[i] = Node(i, a, b);
            fa[i] = l[i] = r[i] = 0;
        }
        sort(node + 1, node + 1 + n);
        top = 0;
        s[top++] = Node(0, 0, -inf);
        for (int i = 1; i <= n; i++) {
            while (s[top-1].b > node[i].b) top--;
            int father = s[top-1].id;
            int id = node[i].id;
            l[id] = r[father];
            fa[r[father]] = id;
            fa[id] = father;
            r[father] = id;
            s[top++] = node[i];
        }
        puts("YES");
        for (int i = 1; i <= n; i++) {
            cout << fa[i] << " " << l[i] << " " << r[i] << endl;
        }
    }
    return 0;
}
