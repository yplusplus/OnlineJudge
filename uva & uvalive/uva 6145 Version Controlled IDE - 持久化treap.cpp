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
    int key, weight, size;
    Node *l, *r;
    Node(int key, int weight, Node *_l, Node *_r) : key(key), weight(weight), l(_l), r(_r) {
        size = 1;
        if (l) size += l->size;
        if (r) size += r->size;
    }
    inline int lsize() { return l ? l->size : 0; }
    inline int rsize() { return r ? r->size : 0; }
} ;

Node *root[55555];

Node *Merge(Node *a, Node *b) {
    if (!a || !b) return a ? a : b;
    return a->weight > b->weight ? new Node(a->key, a->weight, a->l, Merge(a->r, b)) : new Node(b->key, b->weight, Merge(a, b->l), b->r);
}

Node *Split_L(Node *a, int size) {
    if (!a || !size) return NULL;
    if (a->lsize() >= size) return Split_L(a->l, size);
    return new Node(a->key, a->weight, a->l, Split_L(a->r, size - 1 - a->lsize()));
}

Node *Split_R(Node *a, int size) {
    if (!a || !size) return NULL;
    if (a->rsize() >= size) return Split_R(a->r, size);
    return new Node(a->key, a->weight, Split_R(a->l, size - 1 - a->rsize()), a->r);
}

int query(Node *a, int k) {
    //assert(a != NULL);
    if (a->lsize() >= k) return query(a->l, k);
    k -= a->lsize() + 1;
    if (k == 0) return a->key;
    return query(a->r, k);
}

int main() {
    int n;
    scanf("%d", &n);
    root[0] = NULL;
    int len = 0, d = 0, cnt = 1;
    int cmd, pos, v, c;
    char str[111];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cmd);
        if (cmd == 1) {
            scanf("%d%s", &pos, str);
            pos -= d;
            Node *l = Split_L(root[cnt - 1], pos);
            Node *r = Split_R(root[cnt - 1], len - pos);
            for (int j = 0; str[j]; j++) {
                l = Merge(l, new Node(str[j], rand(), NULL, NULL));
                len++;
            }
            root[cnt++] = Merge(l, r);
            //assert(root[cnt - 1] != NULL);
        } else if (cmd == 2) {
            scanf("%d%d", &pos, &c);
            pos -= d, c -= d;
            Node *l = Split_L(root[cnt - 1], pos - 1);
            Node *r = Split_R(root[cnt - 1], len - pos - c + 1);
            root[cnt++] = Merge(l, r);
            //assert(root[cnt - 1] != NULL);
            len -= c;
        } else {
            scanf("%d%d%d", &v, &pos, &c);
            v -= d, pos -= d, c -= d;
            //cout << v << " " << pos << " " << c << endl;
            for (int i = 0; i < c; i++) {
                //cout << pos + i << endl;
                //cout << v << endl;
                //cout << cnt << endl;
                int ch = query(root[v], pos + i);
                d += (ch == 'c');
                printf("%c", ch);
            }
            puts("");
        }
    }
    return 0;
}
