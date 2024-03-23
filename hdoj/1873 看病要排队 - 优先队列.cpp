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

struct Node {
    int lv, id;
    Node(){}
    Node(int _lv, int _id) {
        lv = _lv, id = _id;
    }
    bool operator<(const Node &x) const {
        if (lv != x.lv) return lv < x.lv;
        else return id > x.id;
    }
};
int n;
int main() {
    while (~scanf("%d", &n)) {
        priority_queue<Node> que[3];
        int id = 0;
        while (n--) {
            int a, b;
            string op;
            cin >> op >> a;
            a--;
            if (op[0] == 'I') {
                cin >> b;
                que[a].push(Node(b, ++id));
            } else {
                if (que[a].empty()) {
                    puts("EMPTY");
                } else {
                    printf("%d\n", que[a].top().id);
                    que[a].pop();
                }
            }
        }
    }
    return 0;
}
