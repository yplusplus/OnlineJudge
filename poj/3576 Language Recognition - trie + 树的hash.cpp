#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <cstring>
#include <cstdio>
using namespace std;

#define MP make_pair
typedef pair<long long, long long> pll;
const int KIND = 26;
const pll MOD = MP(6400013, 1000000007);
const pll FINAL = MP(1, 1);
const pll KEY1 = MP(1600033, 31);
const pll KEY2 = MP(131, 400009);

pll operator % (const pll &a, const pll &b) { return MP(a.first % b.first, a.second % b.second); }
pll operator * (const pll &a, const pll &b) { return MP(a.first * b.first, a.second * b.second); }
pll operator + (const pll &a, const pll &b) { return MP(a.first + b.first, a.second + b.second); }

struct Node {
    int child[KIND];
    bool terminal;
    int size;
    void init() { size = 0; memset(child, -1, sizeof(child)); }
} node[155555];

struct Trie {
    int root, tot;
    set<pll> hash;
    void clear() { root = tot = 0; hash.clear(); node[root].init(); }
    void insert(char *str) {
        int p = root;
        while (*str) {
            int idx = *str - 'a';
            if (node[p].child[idx] == -1) {
                node[p].size++;
                node[p].child[idx] = ++tot;
                node[tot].init();
            }
            p = node[p].child[idx];
            str++;
        }
        node[p].terminal = true;
    }
    pll dfs(int u) {
        pll res = MP(0, 0);
        for (int i = 0; i < KIND; i++) {
            pll son = MP(0, 0);
            if (node[u].child[i] != -1) { son = dfs(node[u].child[i]); }
            res = (res * KEY1 + son * KEY2) % MOD;
        }
        pll tmp = MP(1, 1);
        if (node[u].terminal) tmp = tmp + FINAL;
        res = (res * MP(3, 2) + tmp) % MOD;
        hash.insert(res);
        return res;
    }
    int calc() {
        dfs(root);
        return hash.size();
    }
} trie;

int main() {
    int n;
    char str[50];
    scanf("%d", &n);
    trie.clear();
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        trie.insert(str);
    }
    printf("%d\n", trie.calc());
    return 0;
}
