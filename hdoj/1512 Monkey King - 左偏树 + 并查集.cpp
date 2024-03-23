#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;

const int N = 111111;
int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

struct Node {
    int value, dist;
    Node *left, *right;
    Node *fa;
    void init(int _value) {
        value = _value;
        dist = 0;
        fa = left = right = NULL;
    }
} node[N];

Node *Merge(Node *a, Node *b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    if (a->value < b->value) swap(a, b);
    a->right = Merge(a->right, b);
    if (a->left == NULL || a->right->dist > a->left->dist) swap(a->left, a->right);
    if (a->right == NULL) a->dist = 0;
    else a->dist = a->right->dist + 1;
    return a;
}

Node *Delete(Node *x) {
    Node *q = x->fa;
    Node *p = Merge(x->left, x->right);
    p->fa = q;
    if (fa != NULL && q->left == x) q->left = p;
    if (fa != NULL && q->right == x) q->right = p;
    while (q) {
        if (q->right != NULL && (q->left == NULL || q->left->dist < q->right->dist)) 
            swap(q->left, q->right);
        int dist = (q->right == NULL ? 0 : q->right->dist) + 1;
        if (dist != q->dist) q->dist = dist;
        p = q;
        q = q->fa;
    }
    x->fa = x->left = x->right = NULL;
    x->dist = 0;
    return p;
}

Node *root[N];
int n, m;

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1, x; i <= n; i++) {
            scanf("%d", &x);
            node[i].init(x);
            root[i] = &node[i];
            fa[i] = i;
        }
        scanf("%d", &m);
        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            int aid = find(a), bid = find(b);
            if (aid == bid) puts("-1");
            else {
                Node *anode = root[aid];
                Node *bnode = root[bid];
                fa[aid] = bid;
                root[bid] = Merge(Merge(anode->left, anode->right), Merge(bnode->left, bnode->right));
                anode->init(anode->value >> 1);
                bnode->init(bnode->value >> 1);
                root[bid] = Merge(root[bid], Merge(anode, bnode));
                printf("%d\n", root[bid]->value);
            }
        }
    }
    return 0;
}

