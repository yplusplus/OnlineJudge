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

const int N = 11111;
const int bitnum = 30;
int root, tot, n;
struct Node {
    int child[2];
    void init() {
        child[0] = child[1] = 0;
    }
}T[N * bitnum];

void init() {
    tot = root = 0;
    T[root].init();
}

void insert(int x) {
    int p = root;
    for (int i = bitnum; i >= 0; --i) {
        int idx = x >> i & 1;
        if (!T[p].child[idx]) {
            T[++tot].init();
            T[p].child[idx] = tot;
        }
        p = T[p].child[idx];
    }
}

int find(int x) {
    int p = root;
    int res = 0;
    for (int i = bitnum; i >= 0; --i) {
        int idx = x >> i & 1;
        res <<= 1;
        if (T[p].child[idx]) {
            p = T[p].child[idx];
            res |= idx;
        } else {
            p = T[p].child[idx ^ 1];
            res |= (idx ^ 1);
        }
    }
    return res;
}

int main() {
    int T, x;
    char op[10];
    cin >> T;
    while (T--) {
        cin >> n;
        init();
        for (int i = 0; i < n; i++) {
            scanf("%s%d", op, &x);
            if (op[2] == 's') {
                insert(x);
            } else if (op[2] == 'i') {
                printf("%d\n", (x ^ find(x)));
            } else if (op[2] == 'a') {
                printf("%d\n", (x ^ find(~x)));
            }
        }
    }
    return 0;
}
