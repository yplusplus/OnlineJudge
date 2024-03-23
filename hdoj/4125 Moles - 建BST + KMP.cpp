#include <iostream>
#include <cassert>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 600006;
const int M = 7777;
int fail[M];
char s[N * 2], t[M];
int alloc, n;
int mole[N];
struct Node {
    int id;
    Node *left, *right;
    Node() {}
    Node(int _id) : id(_id), left(NULL), right(NULL) {}
} node[N];

map<int, pair<int, Node **> > m;

void get_fail(char *s, int n) {
    int i = 0, j = -1;
    fail[0] = -1;
    while (i < n) {
        if (j == -1 || s[i] == s[j]) {
            i++, j++;
            fail[i] = j;
        } else {
            j = fail[j];
        }
    }
}

void dfs(Node *p) {
    s[alloc++] = p->id % 2 + '0';
    if (p->left) {
        dfs(p->left);
        s[alloc++] = p->id % 2 + '0';
    }
    if (p->right) {
        dfs(p->right);
        s[alloc++] = p->id % 2 + '0';
    }
}

int match(char *s, char *t) {
    int tlen = strlen(t);
    int slen = strlen(s);
    if (slen < tlen) return 0;
    get_fail(t, tlen);
    int i = 0, j = 0;
    int cnt = 0;
    while (i < slen) {
        if (j == tlen) {
            cnt++;
            j = fail[j];
        }
        if (j == -1 || s[i] == t[j]) {
            i++, j++;
        } else {
            j = fail[j];
        }
    }
    if (j == tlen) cnt++;
    return cnt;
}

void solve() {
    alloc = 0;
    m.clear();
    Node *root = NULL;
    m.insert(make_pair(1, make_pair(n, &root)));
    for (int i = 1; i <= n; i++) {
        map<int, pair<int, Node **> >::iterator it = m.upper_bound(mole[i]);
        assert(it != m.begin());
        --it;
        Node *&p = *(it->second.second);
        node[alloc] = Node(mole[i]);
        p = &node[alloc++];
        int l = it->first, r = it->second.first;
        m.erase(it);
        if (l < mole[i]) {
            m.insert(make_pair(l, make_pair(mole[i] - 1, &(p->left))));
        }
        if (mole[i] < r) {
            m.insert(make_pair(mole[i] + 1, make_pair(r, &(p->right))));
        }
    }
    alloc = 0;
    dfs(root);
    s[alloc] = 0;
    printf("%d\n", match(s, t));
}

int main() {
    int T, Case = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &mole[i]);
        scanf("%s", t);
        printf("Case #%d: ", Case++);
        solve();
    }
    return 0;
}

