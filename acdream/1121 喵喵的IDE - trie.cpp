#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;

const int KIND = 26;
const int N = 1000010;
int n;
char str[N];

struct Node {
    int child[KIND];
    int minLen;
    void init() {
        memset(child, 0, sizeof(child));
        minLen = INT_MAX;
    }
} node[N];

struct Trie {
    int root, tot;
    void clear() {
        root = tot = 0;
        node[root].init();
    }
    void insert(char *str, int len) {
        int p = root;
        while (*str) {
            int idx = *str - 'a';
            if (!node[p].child[idx]) {
                node[p].child[idx] = ++tot;
                node[tot].init();
            }
            p = node[p].child[idx];
            node[p].minLen = min(node[p].minLen, len);
            str++;
        }
    }
    int query(char *str, int len) {
        int res = len;
        int p = root;
        int dep = 0;
        while (*str) {
            int idx = *str - 'a';
            if (!node[p].child[idx]) { break; }
            p = node[p].child[idx];
            dep++;
            if (dep > len) break;
            res = min(res, (node[p].minLen - dep) + (len - dep) + 1);
            str++;
        }
        return res;
    }
} trie;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, str);
        trie.clear();
        trie.insert(str, strlen(str));
        for (int i = 1; i <= n; i++) {
            scanf("%s", str);
            int ret = trie.query(str, strlen(str));
            printf("%d\n", ret);
            trie.insert(str, strlen(str));
        }
    }
    return 0;
}
