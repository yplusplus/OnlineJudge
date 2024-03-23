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

struct Node {
    int key, weight, add, rev, Min, size;
    Node *l, *r;
    Node (int key, int weight) : key(key), weight(weight), Min(key) {
        l = r = NULL;
        add = rev = 0;
        size = 1;
    }
    int lsize() { return l ? l->size : 0; }
    int rsize() { return r ? r->size : 0; }
    void pushdown() {
        if (add) {
            if (l) l->add += add, l->Min += add, l->key += add;
            if (r) r->add += add, r->Min += add, r->key += add;
            add = 0;
        }
        if (rev) {
            if (l) swap(l->l, l->r), l->rev ^= 1;
            if (r) swap(r->l, r->r), r->rev ^= 1;
            rev = 0;
        }
    }
    void pushup() {
        Min = key;
        if (l) Min = min(Min, l->Min);
        if (r) Min = min(Min, r->Min);
        size = 1 + lsize() + rsize();
    }
};

Node *merge(Node *a, Node *b) {
    if (!a || !b) return a ? a : b;
    if (a->weight > b->weight) {
        a->pushdown();
        a->r = merge(a->r, b);
        a->pushup();
        return a;
    } else {
        b->pushdown();
        b->l = merge(a, b->l);
        b->pushup();
        return b;
    }
}

void split(Node *p, Node *&a, Node *&b, int size) {
    if (size == 0) { a = NULL, b = p; return; }
    if (size == p->size) { a = p, b = NULL; return; }
    p->pushdown();
    if (p->lsize() >= size) {
        b = p;
        split(p->l, a, b->l, size);
        b->pushup();
    } else {
        a = p;
        split(p->r, a->r, b, size - 1 - p->lsize());
        a->pushup();
    }
}

int main() {
    int n;
    int x, y, z, q;
    scanf("%d", &n);
    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        root = merge(root, new Node(x, rand()));
    }
    Node *a, *b, *c, *d;
    char cmd[20];
    scanf("%d", &q);
    while (q--) {
        scanf("%s", cmd);
        if (cmd[0] == 'I') {
            scanf("%d%d", &x, &y);
            split(root, a, b, x); 
            root = merge(merge(a, new Node(y, rand())), b);
        } else if (cmd[0] == 'D') {
            scanf("%d", &x);
            split(root, a, c, x);
            split(a, a, b, x - 1);
            root = merge(a, c);
        } else if (cmd[0] == 'A') {
            scanf("%d%d%d", &x, &y, &z);
            split(root, a, c, y);
            split(a, a, b, x - 1);
            b->add += z;
            b->Min += z;
            b->key += z;
            root = merge(merge(a, b), c);
        } else if (cmd[0] == 'M') {
            scanf("%d%d", &x, &y);
            split(root, a, c, y);
            split(a, a, b, x - 1);
            printf("%d\n", b->Min);
            root = merge(merge(a, b), c);
        } else if (cmd[3] == 'E') {
            scanf("%d%d", &x, &y);
            split(root, a, c, y);
            split(a, a, b, x - 1);
            b->rev ^= 1;
            swap(b->l, b->r);
            root = merge(merge(a, b), c);
        } else {
            scanf("%d%d%d", &x, &y, &z);
            z = (z % (y - x + 1) + y - x + 1) % (y - x + 1);
            if (!z) continue;
            split(root, a, d, y);
            split(a, a, b, x - 1);
            split(b, b, c, y + 1 - x - z);
            root = merge(merge(a, c), merge(b, d));
        }
    }
    return 0;
}

